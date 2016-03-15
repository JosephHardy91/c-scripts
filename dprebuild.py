# rewrite of datalogger parser fx in Python
import io
import os
import re
from collections import OrderedDict

# acceptable file types
acceptable_file_types = ['.mjr', '.dl4', '.dl5']


# functions to handle reading bytes

def try_int(val):
    if isinstance(val, int):
        return float(val)
    lenv = len(val)
    lv = lenv
    while lv > -1:
        try:
            return float(val[:lv])
        except:
            lv -= 1
    return val


def run_Parser_on_Path(path):
    import pandas as pd
    from pandas import DataFrame as df
    folder_path = path
    root_joint_df = df()
    processed = []
    for sub, dir, files in os.walk(folder_path):
        for file in files:
            fname = os.path.join(sub, file)
            if fname not in processed and os.path.isfile(fname) and os.path.splitext(fname)[
                1].lower() in acceptable_file_types:
                # print fname
                jointname = os.path.splitext(fname)[0] + '.csv'

                f = DLParser(fname)
                # print f.ordered_hash_map
                # print f.graphData

                jointData = f.ordered_hash_map

                closest_sub = os.path.split(sub)[1]
                if closest_sub != jointData['Job_No']:
                    jointData['Job_No'] = closest_sub

                jointData['Identifier'] = '-'.join([jointData['Job_No'], str(jointData['Joint_No'])])
                graphData = f.graphData

                jointData = df(jointData, index=['Identifier'])
                graphData = df.from_dict(graphData)

                # import matplotlib.pyplot as plt
                #
                # plt.plot(f.graphData[0], f.graphData[1])
                # plt.show()

                # jointData.to_csv(jointname, index=False)


                if not os.path.exists(
                        os.path.join(os.path.abspath(folder_path), 'graphData', closest_sub)):
                    if not os.path.exists(os.path.join(os.path.abspath(folder_path), 'graphData')):
                        os.mkdir(os.path.join(os.path.abspath(folder_path), 'graphData'))
                    os.mkdir(os.path.join(os.path.abspath(folder_path), 'graphData', closest_sub))
                graphname = os.path.join(os.path.abspath(folder_path), "graphData", closest_sub,
                                         os.path.split(jointname)[1])

                jointData.ix[0, 'File_Path'] = jointname.replace("\\", "/")
                jointData.ix[0, 'Graph_Path'] = graphname.replace("\\", "/")
                root_joint_df = root_joint_df.append(jointData)
                graphData.T.to_csv(graphname, index=False)
                processed.append(fname)

    root_joint_df.to_csv(os.path.join(folder_path, 'Joint Report Summary.csv'), index=False, quoting=3)


class DLParser(object):
    def __init__(self, file_path):
        self.file_path = file_path
        self.type = self.determine_file_type()
        self.standard = self.determine_standard()
        self.byte_stream = io.BufferedReader(io.open(file_path, 'rb'))
        self.ordered_hash_map, self.graphData = self.read_into_hash()

    def determine_standard(self):
        if self.type == 3:
            return 'utf-16'
        elif self.type == 4:
            return 'latin-1'
        elif self.type == 5:
            return 'latin-1'

    def determine_file_type(self):
        if os.path.splitext(self.file_path)[1].lower() == '.mjr':
            return 3
        elif os.path.splitext(self.file_path)[1].lower() == '.dl4':
            return 4
        elif os.path.splitext(self.file_path)[1].lower() == '.dl5':
            return 5

    def cleanse(self, string, ch=0, replace_rn=True):
        if self.type == 3:
            if '\xb0' in string:
                string = string[:string.find('\xb0')]
            if '\xb2' in string:
                string = string[:string.find('\xb2')]
        elif self.type == 4:
            if '\xa9' in string:
                string = string.replace('\xa9', '')
            string = string.replace('\x00', '')
            if '\xb0' in string:
                string = string.replace('\xb0', ' ')
        elif self.type == 5:
            if '\xa9' in string:
                string = string.replace('\xa9', '')
            string = string.replace('\x00', '')
            if '\xb0' in string:
                string = string.replace('\xb0', ' ')
        if ch == 1:
            string = self.cut_head(string)
        if replace_rn:
            string = string.replace("\n", ' ').replace("\r", '')
        return string.decode(self.standard)

    def cut_head(self, string):
        if len(string) < 1:
            return string
        bad_chars = [" ", "\r", "\n"]
        while string[0] in bad_chars:
            string = string[1:]
        return string

    # DL4/DL5
    def readNextString(self):
        k = self.readNextInt()
        k = int(''.join([str(ord(x)) for x in k]))
        bytesRead = self.byte_stream.read1(k * 2)
        return self.cleanse(bytesRead)

    def readNextStringWithBitFlip(self, replace_rn=True):
        return self.cleanse(self.readNextStringUnfiliteredWithBitFlip(), replace_rn=replace_rn)

    def readNextStringUnfiliteredWithBitFlip(self):
        k = self.readNextInt()
        k = int(''.join([str(ord(x)) for x in k]))
        bytesRead = self.byte_stream.read1(k * 2)
        nbytesRead = []
        for i in range(len(bytesRead)):
            if i % 2 == 0 and i + 1 < len(bytesRead):
                nbytesRead.append(bytesRead[i + 1])
                nbytesRead.append(bytesRead[i])
            elif i % 2 == 0:
                nbytesRead.append(bytesRead[i])
        nbytesRead = ''.join(nbytesRead)
        bytesRead = self.flipBits(nbytesRead)
        return ''.join([x for x in bytesRead])

    def readNextInt(self):
        bytesRead = self.byte_stream.read1(4)
        return bytesRead[::-1]

    def flipBits(self, byte_array):
        return [chr(self.encode_bit_array(self.bnot_mask(self.decode_ord_to_bits(ord(x))))) for x in byte_array]

    def decode_ord_to_bits(self, ordinal):
        maparray = [128, 64, 32, 16, 8, 4, 2, 1]
        byte_array = [0 for _ in range(8)]
        for i in range(len(byte_array)):
            if ordinal - maparray[i] >= 0:
                ordinal -= maparray[i]
                byte_array[i] = 1

        return byte_array

    def bnot_mask(self, b_array):
        return [-1 * b + 1 for b in b_array]

    def encode_bit_array(self, b_array):
        maparray = [128, 64, 32, 16, 8, 4, 2, 1]
        return sum([maparray[i] * b_array[i] for i in range(len(b_array))])

    # DL3
    def readNextRawShort(self):
        bytesRead = self.byte_stream.read1(2)
        return bytesRead[1] + bytesRead[0]

    def readNextShort(self):
        bytesRead = self.byte_stream.read1(2)
        return bytesRead[1] + bytesRead[0]

    def readByteString(self, num_bytes):
        bytesRead = self.byte_stream.read1(num_bytes)
        return bytesRead

    def is_sidewinder(self, val):
        if re.search(val, '/(Sidewinder Mech.)|.* SW/'):
            return True
        else:
            return False

    def formatPipeSizeBeginString(self, val, type):
        if type == 1:
            formatStr = '%s" DIPS ' % val
        elif type == 2:
            formatStr = '%s" O.D. ' % val
        elif type == 3:
            formatStr = "%smm O.D. " % val
        elif type == 4:
            formatStr = "%smm JIS " % val
        else:
            formatStr = '%s" IPS ' % val

        return formatStr

    def formatPipeSizeEndString(self, val, type):
        if type == 1:
            formatStr = "%s\" WT" % val
        elif type == 2:
            formatStr = "%smm WT" % val
        else:
            formatStr = "DR %s" % val

        return formatStr

    def readMJRString(self):
        k = self.readNextRawShort()
        k = int(''.join([str(ord(x)) for x in k]))
        if k == 0:
            self.readNextShort()
            return ""
        else:
            bytesRead = self.byte_stream.read1(k * 2)
            nbytesRead = []
            for i in range(len(bytesRead)):
                if i % 2 == 0 and i + 1 < len(bytesRead):
                    nbytesRead.append(bytesRead[i + 1])
                    nbytesRead.append(bytesRead[i])
                elif i % 2 == 0:
                    nbytesRead.append(bytesRead[i])
            nbytesRead = ''.join(nbytesRead)
            return self.cleanse(nbytesRead)

    # Read Into Hash
    def read_into_hash(self):
        if self.type == 3:
            return self.read_dl3_into_hash()
        elif self.type == 4:
            return self.read_dl4_into_hash()
        elif self.type == 5:
            return self.read_dl5_into_hash()
        else:
            raise IOError("Type unable to be detected.")

    def read_dl3_into_hash(self):
        data = OrderedDict()

        fileVersion = self.readByteString(10)
        if fileVersion != "DL3Pv0.2.5":
            raise IOError("Unable to parse file version " + fileVersion)

        data['File_Version'] = fileVersion

        year = ord(self.readNextRawShort()[1]) + 1792
        month, day, hour, minute, second = [int(''.join([str(ord(x)) for x in self.readNextRawShort()])) for _ in
                                            range(5)]
        data['DateTime'] = "%d/%d/%d %02d:%02d:%02d" % (year, month, day, hour, minute, second)
        data['MachID'] = self.readMJRString()

        self.readNextShort()
        for label in ['MachModel', 'PistonArea']:
            data[label] = self.readMJRString()

        self.readNextShort()
        data['Operator'] = self.readMJRString()
        data['Job_No'] = "'" + self.readMJRString()

        jn_bytes = self.readNextShort()
        data['Joint_No'] = try_int(ord(jn_bytes[0]) + ord(jn_bytes[1]))
        self.readNextShort()
        data['PipeMaterial'] = self.readMJRString()

        if self.is_sidewinder(data['MachModel']):
            data['FittingType'] = self.readMJRString()

            self.readNextShort()

            data['PipeSize'] = self.readMJRString()

            self.readNextShort()

        else:
            data['FittingType'] = ""

            pipeSizeBeginValue = self.readMJRString()
            pipeSizeBeginType = self.readNextShort()
            pipeSizeEndValue = self.readMJRString()
            pipeSizeEndType = self.readNextShort()

            data['PipeSize'] = self.formatPipeSizeBeginString(pipeSizeBeginValue,
                                                              pipeSizeBeginType) + self.formatPipeSizeEndString(
                pipeSizeEndValue, pipeSizeEndType)

        for label in ['BeadIFP', 'SoakIFP', 'FuseIFP', 'CoolIFP']:
            data[label] = try_int(self.readMJRString())

        self.readNextShort()
        for label in ['DragPSI', 'BeadPSI', 'SoakPSI', 'FusePSI', 'CoolPSI']:
            data[label] = try_int(self.readMJRString())

        self.readNextShort()
        for label in ['External_Probe', 'Datalogger_Probe']:
            data[label] = try_int(self.readMJRString())

        for iter_i in range(4):
            self.readNextShort()

        data['Notes'] = self.readMJRString()

        demo = self.readNextShort()

        dataloggerinfo = self.readMJRString()
        data['Datalogger_No'] = "'" + dataloggerinfo[11:15]
        data['Software'] = "v.%s.%s.%s" % (dataloggerinfo[15], dataloggerinfo[16], dataloggerinfo[17])
        data['Calibration_Date'] = "%s/%s/%s" % (dataloggerinfo[18:22], dataloggerinfo[22:24], dataloggerinfo[24:26])

        data['JunkArea'] = try_int(self.readMJRString())

        graphHeader = self.readByteString(20)
        # print graphHeader
        data['GraphMaxPSI'] = try_int(graphHeader[2:6])
        data['GraphMaxTime'] = try_int(graphHeader[8:13]) / 5.0
        data['GraphNumPoints'] = try_int(graphHeader[15:])

        self.readByteString(1)

        graphData = [[], []]
        for i in range(int(data['GraphNumPoints'])):
            time = self.readNextShort()
            pressure = self.readNextShort()

            time = ord(time[0]) * 256 + ord(time[1])
            pressure = ord(pressure[0]) * 256 + ord(pressure[1])

            graphData[0].append(time)
            graphData[1].append(pressure)

        return data, graphData

    def read_dl4_into_hash(self):
        data = OrderedDict()
        fileVersion = self.readNextString().replace("\0", '')
        if fileVersion != "DL4-001":
            raise IOError("Unable to parse file version " + fileVersion)
        data['File_Version'] = fileVersion
        data['Software'] = " ".join([self.readNextStringWithBitFlip(), self.readNextStringWithBitFlip()])
        copyright = self.readNextStringWithBitFlip()
        for label in ['DateTime', 'Operator', 'Job_No']:
            data[label] = self.readNextStringWithBitFlip()
        data['Joint_No'] = int(''.join([str(ord(c)) for c in self.readNextInt()]))
        for label in ['MachID', 'MachModel']:
            data[label] = self.readNextStringWithBitFlip()
        data['PistonArea'] = try_int(self.readNextStringWithBitFlip())
        FusionType = (self.readNextStringWithBitFlip(replace_rn=False)).split("\r")
        data['FusionType'] = FusionType[0].replace("\n", '')
        if len(FusionType) > 1:
            data['FusionStandard'] = self.cut_head(FusionType[1].replace("\n", ''))

        pipeInfo = (self.readNextStringWithBitFlip(replace_rn=False)).split("\r", 3)
        if len(pipeInfo) > 0:
            data['PipeMaterial'] = self.cleanse(pipeInfo[0], ch=1)
        if len(pipeInfo) > 1:
            data['PipeSize'] = self.cleanse(pipeInfo[1], ch=1)
        if len(pipeInfo) > 2:
            data['PipeAngle'] = (self.cleanse(pipeInfo[2])).replace('Angle:', '')

        self.readNextShort()

        pressureUnit = self.readNextStringWithBitFlip()
        for label in ['BeadIFP', 'SoakIFP', 'FuseIFP', 'CoolIFP', 'BeadPSI', 'SoakPSI', 'FusePSI', 'CoolPSI']:
            data[label] = try_int(self.readNextStringWithBitFlip())

        for label in ['Heater', 'MinBead', 'SoakTime', 'OpenCloseTime', 'BeadTime', 'FuseCoolTime']:
            data[label] = self.readNextStringWithBitFlip()

        data['DragPSI'] = try_int(self.readNextStringWithBitFlip())

        GraphMaxPSI = int(''.join([str(ord(c)) for c in self.readNextShort()]))

        graphData = [[], []]
        nGP = self.readNextInt()
        nGP_multi = float(''.join(str(ord(c)) for c in nGP[0:2])) if float(
            ''.join(str(ord(c)) for c in nGP[0:2])) > 0 else 1
        numGraphPoints = nGP_multi * 256 * ord(nGP[2]) + ord(nGP[3])
        # numGraphPoints = int(''.join([str(ord(c)) for c in nGP]))
        # print numGraphPoints
        #print data['Joint_No']
        for i in range(numGraphPoints):
            time = self.readNextInt()
            pressure = self.readNextShort()
            #print [ord(c) for c in time]
            time_multi = float(''.join(str(ord(c)) for c in time[0:2]))
            time = time_multi * 256 ** 2 + 256 * ord(time[2]) + ord(time[3])

            pressure = ord(pressure[0]) * 256 + ord(pressure[1])
            #print time, pressure
            graphData[0].append(time)
            graphData[1].append(pressure)

        data['GraphNumPoints'] = numGraphPoints
        data['GraphMaxTime'] = graphData[0][-1] / 1000.0

        data['Notes'] = self.readNextStringWithBitFlip()
        # print len(graphData[0])
        # if data['Joint_No'] == 1:
        # print graphData[1]
        # print data['Notes']
        starttime = self.readNextStringWithBitFlip()
        for label in ['Computer', 'Datalogger_No', 'Calibration_Date', 'Firmware']:
            data[label] = self.readNextStringWithBitFlip()
        self.readNextInt()

        data['External_Probe'] = self.readNextStringWithBitFlip()
        return data, graphData

    def read_dl5_into_hash(self):
        data = OrderedDict()
        fileVersion = self.readNextString().replace("\0", '')
        if fileVersion != "DL5-002":
            raise IOError("Unable to parse file version " + fileVersion)
        data['File_Version'] = fileVersion
        data['Software'] = " ".join([self.readNextStringWithBitFlip(), self.readNextStringWithBitFlip()])
        copyright = self.readNextStringWithBitFlip()
        for label in ['DateTime', 'Operator', 'Job_No']:
            data[label] = self.readNextStringWithBitFlip()
        data['Joint_No'] = int(''.join([str(ord(c)) for c in self.readNextInt()]))
        for label in ['MachID', 'MachModel']:
            data[label] = self.readNextStringWithBitFlip()
        data['PistonArea'] = try_int(self.readNextStringWithBitFlip())
        FusionType = (self.readNextStringWithBitFlip(replace_rn=False)).split("\r")
        data['FusionType'] = FusionType[0].replace("\n", '')
        if len(FusionType) > 1:
            data['FusionStandard'] = self.cut_head(FusionType[1].replace("\n", ''))

        pipeInfo = (self.readNextStringWithBitFlip(replace_rn=False)).split("\r", 3)
        if len(pipeInfo) > 0:
            data['PipeMaterial'] = self.cleanse(pipeInfo[0], ch=1)
        if len(pipeInfo) > 1:
            data['PipeSize'] = self.cleanse(pipeInfo[1], ch=1)
        if len(pipeInfo) > 2:
            data['PipeAngle'] = (self.cleanse(pipeInfo[2])).replace('Angle:', '')

        self.readNextShort()

        pressureUnit = self.readNextStringWithBitFlip()
        for label in ['BeadIFP', 'SoakIFP', 'FuseIFP', 'CoolIFP', 'BeadPSI', 'SoakPSI', 'FusePSI', 'CoolPSI']:
            data[label] = try_int(self.readNextStringWithBitFlip())

        for label in ['Heater', 'MinBead', 'SoakTime', 'OpenCloseTime', 'BeadTime', 'FuseCoolTime']:
            data[label] = self.readNextStringWithBitFlip()

        data['DragPSI'] = try_int(self.readNextStringWithBitFlip())

        GraphMaxPSI = int(''.join([str(ord(c)) for c in self.readNextShort()]))

        graphData = [[], []]
        nGP = self.readNextInt()
        nGP_multi = float(''.join(str(ord(c)) for c in nGP[0:2])) if float(
            ''.join(str(ord(c)) for c in nGP[0:2])) > 0 else 1
        numGraphPoints = nGP_multi * 256 * ord(nGP[2]) + ord(nGP[3])
        # numGraphPoints = int(''.join([str(ord(c)) for c in nGP]))
        # print numGraphPoints
        #print data['Joint_No']
        for i in range(numGraphPoints):
            time = self.readNextInt()
            pressure = self.readNextShort()
            #print [ord(c) for c in time]
            time_multi = float(''.join(str(ord(c)) for c in time[0:2]))
            time = time_multi * 256 ** 2 + 256 * ord(time[2]) + ord(time[3])

            pressure = ord(pressure[0]) * 256 + ord(pressure[1])
            #print time, pressure
            graphData[0].append(time)
            graphData[1].append(pressure)

        data['GraphNumPoints'] = numGraphPoints
        data['GraphMaxTime'] = graphData[0][-1] / 1000.0

        data['Notes'] = self.readNextStringWithBitFlip()
        # print len(graphData[0])
        # if data['Joint_No'] == 1:
        # print graphData[1]
        # print data['Notes']
        starttime = self.readNextStringWithBitFlip()
        for label in ['Computer', 'Datalogger_No', 'Calibration_Date', 'Firmware']:
            data[label] = self.readNextStringWithBitFlip()
        self.readNextInt()

        data['External_Probe'] = self.readNextStringWithBitFlip()
        return data, graphData


if __name__ == "__main__":
    import pandas as pd
    from pandas import DataFrame as df
    import time

    t1 = time.clock()
    folder_path = r'C:\Users\joe\Dropbox (ISCO)\Graphomatic 3000\not working\001 Home\01220075'.replace("\\", "/")
    root_joint_df = df()
    for file in os.listdir(folder_path):
        fname = os.path.join(folder_path, file)
        if os.path.isfile(fname) and os.path.splitext(fname)[1].lower() in acceptable_file_types:

            print fname

            # from BeautifulSoup import BeautifulSoup
            # soup=BeautifulSoup(open(fname,'r').read())
            # print soup.originalEncoding

            jointname = os.path.splitext(fname)[0] + '.csv'
            if not os.path.exists(os.path.abspath(folder_path) + "/graphData/"):
                os.mkdir(os.path.abspath(folder_path) + "/graphData/")
            graphname = os.path.abspath(folder_path) + "/graphData/" + os.path.split(jointname)[1]
            f = DLParser(fname)


            # print f.ordered_hash_map
            # print f.graphData

            jointData = f.ordered_hash_map
            graphData = f.graphData
            jointData = df(jointData, index=[0])
            graphData = df(graphData)

            # import matplotlib.pyplot as plt
            #
            # plt.plot(f.graphData[0], f.graphData[1])
            # plt.show()

            # jointData.to_csv(jointname, index=False)
            root_joint_df = root_joint_df.append(jointData)
            graphData.T.to_csv(graphname, index=False)

    root_joint_df.to_excel(os.path.join(folder_path, 'Joint Report Summary.xlsx'), index=False)
    print time.clock() - t1
