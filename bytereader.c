#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>
#include <locale.h>
#include <sys/types.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>

int bsmarker;




typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

//convenience functions
void printString(char *stringa){
	int i;
	for(i=0;i<strlen(stringa);i++){
		putchar(stringa[i]);
	}
	putchar('\n');
}

void printArray(Array arr){
	int i;
	for(i=0;i<arr.used;i++){
		putchar(arr.array[i]);
	}
	putchar('\n');
}

//data array

Array data;


Array constructmjrReportHeaders(){
	Array headerArray;
	initArray(&headerArray,(size_t)25);
	int i=0;
	char *BeadPSI="BeadPSI,";
	char *BeadIFP="BeadIFP,";
	char *CoolPSI="CoolPSI,";
	char *CoolIFP="CoolIFP,";
	char *Datalogger_Probe="Datalogger_Probe,";
	char *DateTime="DateTime,";
	char *DragPSI="DragPSI,";
	char *Operator="Operator,";
	char *External_Probe="External_Probe,";
	char *FusionType="FusionType,";
	char *File_Version="File_Version,";
	char *FusePSI="FusePSI,";
	char *FuseIFP="FuseIFP,";
	char *Graph_Header="Graph_Header,";
	char *GraphMaxPSI="GraphMaxPSI,";
	char *GraphMaxTime5="GraphMaxTime5,";
	char *GraphNumPoints="GraphNumPoints,";
	char *Job_No="Job_No,";
	char *Joint_No="Joint_No,";
	char *MachModel="MachModel,";
	char *MachID="MachID,";
	char *Notes="Notes,";
	char *Path_to_graph_data="Path_to_graph_data,";
	char *PipeMaterial="PipeMaterial,";
	char *PipeSize="PipeSize,";
	char *PistonArea="PistonArea,";
	char *SoakPSI="SoakPSI,";
	char *SoakIFP="SoakIFP,";
	char *UnknownArea="UnknownArea,";
	char *Software="Software,";
	char *Path_to_data_file="Path_to_data_file,";
	for(i=0;i<strlen(BeadPSI);i++){insertArray(&headerArray,BeadPSI[i]);}
	for(i=0;i<strlen(BeadIFP);i++){insertArray(&headerArray,BeadIFP[i]);}
	for(i=0;i<strlen(CoolPSI);i++){insertArray(&headerArray,CoolPSI[i]);}
	for(i=0;i<strlen(CoolIFP);i++){insertArray(&headerArray,CoolIFP[i]);}
	for(i=0;i<strlen(Datalogger_Probe);i++){insertArray(&headerArray,Datalogger_Probe[i]);}
	for(i=0;i<strlen(DateTime);i++){insertArray(&headerArray,DateTime[i]);}
	for(i=0;i<strlen(DragPSI);i++){insertArray(&headerArray,DragPSI[i]);}
	for(i=0;i<strlen(Operator);i++){insertArray(&headerArray,Operator[i]);}
	for(i=0;i<strlen(External_Probe);i++){insertArray(&headerArray,External_Probe[i]);}
	for(i=0;i<strlen(FusionType);i++){insertArray(&headerArray,FusionType[i]);}
	for(i=0;i<strlen(File_Version);i++){insertArray(&headerArray,File_Version[i]);}
	for(i=0;i<strlen(FusePSI);i++){insertArray(&headerArray,FusePSI[i]);}
	for(i=0;i<strlen(FuseIFP);i++){insertArray(&headerArray,FuseIFP[i]);}
	for(i=0;i<strlen(Graph_Header);i++){insertArray(&headerArray,Graph_Header[i]);}
	for(i=0;i<strlen(GraphMaxPSI);i++){insertArray(&headerArray,GraphMaxPSI[i]);}
	for(i=0;i<strlen(GraphMaxTime5);i++){insertArray(&headerArray,GraphMaxTime5[i]);}
	for(i=0;i<strlen(GraphNumPoints);i++){insertArray(&headerArray,GraphNumPoints[i]);}
	for(i=0;i<strlen(Job_No);i++){insertArray(&headerArray,Job_No[i]);}
	for(i=0;i<strlen(Joint_No);i++){insertArray(&headerArray,Joint_No[i]);}
	for(i=0;i<strlen(MachModel);i++){insertArray(&headerArray,MachModel[i]);}
	for(i=0;i<strlen(MachID);i++){insertArray(&headerArray,MachID[i]);}
	for(i=0;i<strlen(Notes);i++){insertArray(&headerArray,Notes[i]);}
	for(i=0;i<strlen(Path_to_graph_data);i++){insertArray(&headerArray,Path_to_graph_data[i]);}
	for(i=0;i<strlen(PipeMaterial);i++){insertArray(&headerArray,PipeMaterial[i]);}
	for(i=0;i<strlen(PipeSize);i++){insertArray(&headerArray,PipeSize[i]);}
	for(i=0;i<strlen(PistonArea);i++){insertArray(&headerArray,PistonArea[i]);}
	for(i=0;i<strlen(SoakPSI);i++){insertArray(&headerArray,SoakPSI[i]);}
	for(i=0;i<strlen(SoakIFP);i++){insertArray(&headerArray,SoakIFP[i]);}
	for(i=0;i<strlen(UnknownArea);i++){insertArray(&headerArray,UnknownArea[i]);}
	for(i=0;i<strlen(Software);i++){insertArray(&headerArray,Software[i]);}
	for(i=0;i<strlen(Path_to_data_file);i++){insertArray(&headerArray,Path_to_data_file[i]);}
	insertArray(&headerArray,'\0');
	return headerArray;
}

Array constructdl4ReportHeaders(){
	Array headerArray;
	initArray(&headerArray,(size_t)25);
	int i=0;
	char *BeadTime="BeadTime,";
	char *BeadIFP="BeadIFP,";
	char *BeadPSI="BeadPSI,";
	char *Calibration_Date="Calibration_Date,";
	char *Computer="Computer,";
	char *CoolIFP="CoolIFP,";
	char *CoolPSI="CoolPSI,";
	char *Datalogger_No="Datalogger_No,";
	char *DateTime="DateTime,";
	char *DragPSI="DragPSI,";
	char *External_Probe="External_Probe,";
	char *File_Version="File_Version,";
	char *Firmware="Firmware,";
	char *FuseIFP="FuseIFP,";
	char *FusePSI="FusePSI,";
	char *FuseTime="FuseTime,";
	char *FusionType="FusionType,";
	char *GraphMaxPSI="GraphMaxPSI,";
	char *GraphNumPoints="GraphNumPoints,";
	char *SoakIFP="SoakIFP,";
	char *SoakPSI="SoakPSI,";
	char *SoakTime="SoakTime,";
	char *Heater="Heater,";
	char *Job_No="Job_No,";
	char *Joint_No="Joint_No,";
	char *MachModel="MachModel,";
	char *MachID="MachID,";
	char *MinBead="MinBead,";
	char *Notes="Notes,";
	char *DwellTime="DwellTime,";
	char *Operator="Operator,";
	char *Path_to_graph_data="Path_to_graph_data,";
	char *Pipe="Pipe,";
	char *PistonArea="PistonArea,";
	char *Software="Software,";
	char *Starttime="Starttime,";
	char *Path_to_data_file="Path_to_data_file,";
	for(i=0;i<strlen(BeadTime);i++){insertArray(&headerArray,BeadTime[i]);}
	for(i=0;i<strlen(BeadIFP);i++){insertArray(&headerArray,BeadIFP[i]);}
	for(i=0;i<strlen(BeadPSI);i++){insertArray(&headerArray,BeadPSI[i]);}
	for(i=0;i<strlen(Calibration_Date);i++){insertArray(&headerArray,Calibration_Date[i]);}
	for(i=0;i<strlen(Computer);i++){insertArray(&headerArray,Computer[i]);}
	for(i=0;i<strlen(CoolIFP);i++){insertArray(&headerArray,CoolIFP[i]);}
	for(i=0;i<strlen(CoolPSI);i++){insertArray(&headerArray,CoolPSI[i]);}
	for(i=0;i<strlen(Datalogger_No);i++){insertArray(&headerArray,Datalogger_No[i]);}
	for(i=0;i<strlen(DateTime);i++){insertArray(&headerArray,DateTime[i]);}
	for(i=0;i<strlen(DragPSI);i++){insertArray(&headerArray,DragPSI[i]);}
	for(i=0;i<strlen(External_Probe);i++){insertArray(&headerArray,External_Probe[i]);}
	for(i=0;i<strlen(File_Version);i++){insertArray(&headerArray,File_Version[i]);}
	for(i=0;i<strlen(Firmware);i++){insertArray(&headerArray,Firmware[i]);}
	for(i=0;i<strlen(FuseIFP);i++){insertArray(&headerArray,FuseIFP[i]);}
	for(i=0;i<strlen(FusePSI);i++){insertArray(&headerArray,FusePSI[i]);}
	for(i=0;i<strlen(FuseTime);i++){insertArray(&headerArray,FuseTime[i]);}
	for(i=0;i<strlen(FusionType);i++){insertArray(&headerArray,FusionType[i]);}
	for(i=0;i<strlen(GraphMaxPSI);i++){insertArray(&headerArray,GraphMaxPSI[i]);}
	for(i=0;i<strlen(GraphNumPoints);i++){insertArray(&headerArray,GraphNumPoints[i]);}
	for(i=0;i<strlen(SoakIFP);i++){insertArray(&headerArray,SoakIFP[i]);}
	for(i=0;i<strlen(SoakPSI);i++){insertArray(&headerArray,SoakPSI[i]);}
	for(i=0;i<strlen(SoakTime);i++){insertArray(&headerArray,SoakTime[i]);}
	for(i=0;i<strlen(Heater);i++){insertArray(&headerArray,Heater[i]);}
	for(i=0;i<strlen(Job_No);i++){insertArray(&headerArray,Job_No[i]);}
	for(i=0;i<strlen(Joint_No);i++){insertArray(&headerArray,Joint_No[i]);}
	for(i=0;i<strlen(MachModel);i++){insertArray(&headerArray,MachModel[i]);}
	for(i=0;i<strlen(MachID);i++){insertArray(&headerArray,MachID[i]);}
	for(i=0;i<strlen(MinBead);i++){insertArray(&headerArray,MinBead[i]);}
	for(i=0;i<strlen(Notes);i++){insertArray(&headerArray,Notes[i]);}
	for(i=0;i<strlen(DwellTime);i++){insertArray(&headerArray,DwellTime[i]);}
	for(i=0;i<strlen(Operator);i++){insertArray(&headerArray,Operator[i]);}
	for(i=0;i<strlen(Path_to_graph_data);i++){insertArray(&headerArray,Path_to_graph_data[i]);}
	for(i=0;i<strlen(Pipe);i++){insertArray(&headerArray,Pipe[i]);}
	for(i=0;i<strlen(PistonArea);i++){insertArray(&headerArray,PistonArea[i]);}
	for(i=0;i<strlen(Software);i++){insertArray(&headerArray,Software[i]);}
	for(i=0;i<strlen(Starttime);i++){insertArray(&headerArray,Starttime[i]);}
	for(i=0;i<strlen(Path_to_data_file);i++){insertArray(&headerArray,Path_to_data_file[i]);}
	insertArray(&headerArray,'\0');
	
	return headerArray;
}

Array constructmjrHeaders(){
	Array headerArray;
	initArray(&headerArray,(size_t)25);
	int i=0;
	char *FileVersion="FileVersion,";
	char *DateTime="DateTime,";
	char *MachID="MachID,";
	char *MachModel="MachModel,";
	char *PistonArea="PistonArea,";
	char *Operator="Operator,";
	char *Job_No="Job_No,";
	char *Joint_No="Joint_No,";
	char *PipeMaterial="PipeMaterial,";
	char *FittingType="FittingType,";
	char *PipeSize="PipeSize,";
	char *BeadIFP="BeadIFP,";
	char *SoakIFP="SoakIFP,";
	char *FuseIFP="FuseIFP,";
	char *CoolIFP="CoolIFP,";
	char *DragPSI="DragPSI,";
	char *BeadPSI="BeadPSI,";
	char *SoakPSI="SoakPSI,";
	char *FusePSI="FusePSI,";
	char *CoolPSI="CoolPSI,";
	char *External_Probe="External_Probe,";
	char *Datalogger_Probe="Datalogger_Probe,";
	char *Notes="Notes,";
	char *Datalogger_No="Datalogger_No,";
	char *Software="Software,";
	char *Calibration_Date="Calibration_Date,";
	char *JunkArea="JunkArea,";
	char *GraphMaxPSI="GraphMaxPSI,";
	char *GraphMaxTime="GraphMaxTime,";
	char *GraphNumPoints="GraphNumPoints,";
	for(i=0;i<strlen(FileVersion);i++){insertArray(&headerArray,FileVersion[i]);}
	for(i=0;i<strlen(DateTime);i++){insertArray(&headerArray,DateTime[i]);}
	for(i=0;i<strlen(MachID);i++){insertArray(&headerArray,MachID[i]);}
	for(i=0;i<strlen(MachModel);i++){insertArray(&headerArray,MachModel[i]);}
	for(i=0;i<strlen(PistonArea);i++){insertArray(&headerArray,PistonArea[i]);}
	for(i=0;i<strlen(Operator);i++){insertArray(&headerArray,Operator[i]);}
	for(i=0;i<strlen(Job_No);i++){insertArray(&headerArray,Job_No[i]);}
	for(i=0;i<strlen(Joint_No);i++){insertArray(&headerArray,Joint_No[i]);}
	for(i=0;i<strlen(PipeMaterial);i++){insertArray(&headerArray,PipeMaterial[i]);}
	for(i=0;i<strlen(FittingType);i++){insertArray(&headerArray,FittingType[i]);}
	for(i=0;i<strlen(PipeSize);i++){insertArray(&headerArray,PipeSize[i]);}
	for(i=0;i<strlen(BeadIFP);i++){insertArray(&headerArray,BeadIFP[i]);}
	for(i=0;i<strlen(SoakIFP);i++){insertArray(&headerArray,SoakIFP[i]);}
	for(i=0;i<strlen(FuseIFP);i++){insertArray(&headerArray,FuseIFP[i]);}
	for(i=0;i<strlen(CoolIFP);i++){insertArray(&headerArray,CoolIFP[i]);}
	for(i=0;i<strlen(DragPSI);i++){insertArray(&headerArray,DragPSI[i]);}
	for(i=0;i<strlen(BeadPSI);i++){insertArray(&headerArray,BeadPSI[i]);}
	for(i=0;i<strlen(SoakPSI);i++){insertArray(&headerArray,SoakPSI[i]);}
	for(i=0;i<strlen(FusePSI);i++){insertArray(&headerArray,FusePSI[i]);}
	for(i=0;i<strlen(CoolPSI);i++){insertArray(&headerArray,CoolPSI[i]);}
	for(i=0;i<strlen(External_Probe);i++){insertArray(&headerArray,External_Probe[i]);}
	for(i=0;i<strlen(Datalogger_Probe);i++){insertArray(&headerArray,Datalogger_Probe[i]);}
	for(i=0;i<strlen(Notes);i++){insertArray(&headerArray,Notes[i]);}
	for(i=0;i<strlen(Datalogger_No);i++){insertArray(&headerArray,Datalogger_No[i]);}
	for(i=0;i<strlen(Software);i++){insertArray(&headerArray,Software[i]);}
	for(i=0;i<strlen(Calibration_Date);i++){insertArray(&headerArray,Calibration_Date[i]);}
	for(i=0;i<strlen(JunkArea);i++){insertArray(&headerArray,JunkArea[i]);}
	for(i=0;i<strlen(GraphMaxPSI);i++){insertArray(&headerArray,GraphMaxPSI[i]);}
	for(i=0;i<strlen(GraphMaxTime);i++){insertArray(&headerArray,GraphMaxTime[i]);}
	for(i=0;i<strlen(GraphNumPoints);i++){insertArray(&headerArray,GraphNumPoints[i]);}
	insertArray(&headerArray,'\0');
	
	return headerArray;
}
Array constructdl4Headers(){
	Array headerArray;
	initArray(&headerArray,(size_t)25);
	int i=0;
	char *FileVersion="FileVersion,";
	char *Software="Software,";
	char *DateTime="DateTime,";
	char *Operator="Operator,";
	char *Job_No="Job_No,";
	char *Joint_No="Joint_No,";
	char *MachID="MachID,";
	char *MachModel="MachModel,";
	char *PistonArea="PistonArea,";
	char *FusionType="FusionType,";
	char *FusionStandard="FusionStandard,";
	char *PipeMaterial="PipeMaterial,";
	char *PipeSize="PipeSize,";
	char *PipeAngle="PipeAngle,";
	char *BeadIFP="BeadIFP,";
	char *SoakIFP="SoakIFP,";
	char *FuseIFP="FuseIFP,";
	char *CoolIFP="CoolIFP,";
	char *BeadPSI="BeadPSI,";
	char *SoakPSI="SoakPSI,";
	char *FusePSI="FusePSI,";
	char *CoolPSI="CoolPSI,";
	char *Heater="Heater,";
	char *MinBead="MinBead,";
	char *SoakTime="SoakTime,";
	char *OpenCloseTime="OpenCloseTime,";
	char *BeadTime="BeadTime,";
	char *FuseCoolTime="FuseCoolTime,";
	char *DragPSI="DragPSI,";
	char *GraphNumPoints="GraphNumPoints,";
	char *GraphMaxTime="GraphMaxTime,";
	char *Notes="Notes,";
	char *Computer="Computer,";
	char *Datalogger_No="Datalogger_No,";
	char *Calibration_Date="Calibration_Date,";
	char *Firmware="Firmware,";
	char *External_Probe="External_Probe,";
	for(i=0;i<strlen(FileVersion);i++){insertArray(&headerArray,FileVersion[i]);}
	for(i=0;i<strlen(Software);i++){insertArray(&headerArray,Software[i]);}
	for(i=0;i<strlen(DateTime);i++){insertArray(&headerArray,DateTime[i]);}
	for(i=0;i<strlen(Operator);i++){insertArray(&headerArray,Operator[i]);}
	for(i=0;i<strlen(Job_No);i++){insertArray(&headerArray,Job_No[i]);}
	for(i=0;i<strlen(Joint_No);i++){insertArray(&headerArray,Joint_No[i]);}
	for(i=0;i<strlen(MachID);i++){insertArray(&headerArray,MachID[i]);}
	for(i=0;i<strlen(MachModel);i++){insertArray(&headerArray,MachModel[i]);}
	for(i=0;i<strlen(PistonArea);i++){insertArray(&headerArray,PistonArea[i]);}
	for(i=0;i<strlen(FusionType);i++){insertArray(&headerArray,FusionType[i]);}
	for(i=0;i<strlen(FusionStandard);i++){insertArray(&headerArray,FusionStandard[i]);}
	for(i=0;i<strlen(PipeMaterial);i++){insertArray(&headerArray,PipeMaterial[i]);}
	for(i=0;i<strlen(PipeSize);i++){insertArray(&headerArray,PipeSize[i]);}
	for(i=0;i<strlen(PipeAngle);i++){insertArray(&headerArray,PipeAngle[i]);}
	for(i=0;i<strlen(BeadIFP);i++){insertArray(&headerArray,BeadIFP[i]);}
	for(i=0;i<strlen(SoakIFP);i++){insertArray(&headerArray,SoakIFP[i]);}
	for(i=0;i<strlen(FuseIFP);i++){insertArray(&headerArray,FuseIFP[i]);}
	for(i=0;i<strlen(CoolIFP);i++){insertArray(&headerArray,CoolIFP[i]);}
	for(i=0;i<strlen(BeadPSI);i++){insertArray(&headerArray,BeadPSI[i]);}
	for(i=0;i<strlen(SoakPSI);i++){insertArray(&headerArray,SoakPSI[i]);}
	for(i=0;i<strlen(FusePSI);i++){insertArray(&headerArray,FusePSI[i]);}
	for(i=0;i<strlen(CoolPSI);i++){insertArray(&headerArray,CoolPSI[i]);}
	for(i=0;i<strlen(Heater);i++){insertArray(&headerArray,Heater[i]);}
	for(i=0;i<strlen(MinBead);i++){insertArray(&headerArray,MinBead[i]);}
	for(i=0;i<strlen(SoakTime);i++){insertArray(&headerArray,SoakTime[i]);}
	for(i=0;i<strlen(OpenCloseTime);i++){insertArray(&headerArray,OpenCloseTime[i]);}
	for(i=0;i<strlen(BeadTime);i++){insertArray(&headerArray,BeadTime[i]);}
	for(i=0;i<strlen(FuseCoolTime);i++){insertArray(&headerArray,FuseCoolTime[i]);}
	for(i=0;i<strlen(DragPSI);i++){insertArray(&headerArray,DragPSI[i]);}
	for(i=0;i<strlen(GraphNumPoints);i++){insertArray(&headerArray,GraphNumPoints[i]);}
	for(i=0;i<strlen(GraphMaxTime);i++){insertArray(&headerArray,GraphMaxTime[i]);}
	for(i=0;i<strlen(Notes);i++){insertArray(&headerArray,Notes[i]);}
	for(i=0;i<strlen(Computer);i++){insertArray(&headerArray,Computer[i]);}
	for(i=0;i<strlen(Datalogger_No);i++){insertArray(&headerArray,Datalogger_No[i]);}
	for(i=0;i<strlen(Calibration_Date);i++){insertArray(&headerArray,Calibration_Date[i]);}
	for(i=0;i<strlen(Firmware);i++){insertArray(&headerArray,Firmware[i]);}
	for(i=0;i<strlen(External_Probe);i++){insertArray(&headerArray,External_Probe[i]);}
	insertArray(&headerArray,'\0');
	
	return headerArray;
}

Array constructSummaryHeaders(){
	Array headerArray;
	initArray(&headerArray,(size_t)25);
	int i=0;
	char *BeadLength="BeadLength,";
	char *BeadPSI="BeadPSI,";
	char *BeadIFP="BeadIFP,";
	char *Calibration_Date="Calibration_Date,";
	char *Computer="Computer,";
	char *CoolPSI="CoolPSI,";
	char *CoolIFP="CoolIFP,";
	char *Datalogger_No="Datalogger_No,";
	char *Datalogger_Probe="Datalogger_Probe,";
	char *DateTime="DateTime,";
	char *DragPSI="DragPSI,";
	char *External_Probe="External_Probe,";
	char *FileVersion="FileVersion,";
	char *Firmware="Firmware,";
	char *FittingType="FittingType,";
	char *FusePSI="FusePSI,";
	char *FuseIFP="FuseIFP,";
	char *FuseLength="FuseLength,";
	char *FusionType="FusionType,";
	char *MaxGraphPSI="MaxGraphPSI,";
	char *MaxGraphTime="MaxGraphTime,";
	char *GraphNumPoints="GraphNumPoints,";
	char *SoakPSI="SoakPSI,";
	char *SoakIFP="SoakIFP,";
	char *SoakLength="SoakLength,";
	char *Heater="Heater,";
	char *Job_No="Job_No,";
	char *Joint_No="Joint_No,";
	char *MachID="MachID,";
	char *MachModel="MachModel,";
	char *MinBead="MinBead,";
	char *Notes="Notes,";
	char *DwellTime="DwellTime,";
	char *Operator="Operator,";
	char *Path_to_graph_data="Path_to_graph_data,";
	char *PipeAngle="PipeAngle,";
	char *PipeMaterial="PipeMaterial,";
	char *PipeSize="PipeSize,";
	char *PistonArea="PistonArea,";
	char *Software="Software,";
	char *Path_to_data_file="Path_to_data_file,";
	for(i=0;i<strlen(BeadLength);i++){insertArray(&headerArray,BeadLength[i]);}
	for(i=0;i<strlen(BeadPSI);i++){insertArray(&headerArray,BeadPSI[i]);}
	for(i=0;i<strlen(BeadIFP);i++){insertArray(&headerArray,BeadIFP[i]);}
	for(i=0;i<strlen(Calibration_Date);i++){insertArray(&headerArray,Calibration_Date[i]);}
	for(i=0;i<strlen(Computer);i++){insertArray(&headerArray,Computer[i]);}
	for(i=0;i<strlen(CoolPSI);i++){insertArray(&headerArray,CoolPSI[i]);}
	for(i=0;i<strlen(CoolIFP);i++){insertArray(&headerArray,CoolIFP[i]);}
	for(i=0;i<strlen(Datalogger_No);i++){insertArray(&headerArray,Datalogger_No[i]);}
	for(i=0;i<strlen(Datalogger_Probe);i++){insertArray(&headerArray,Datalogger_Probe[i]);}
	for(i=0;i<strlen(DateTime);i++){insertArray(&headerArray,DateTime[i]);}
	for(i=0;i<strlen(DragPSI);i++){insertArray(&headerArray,DragPSI[i]);}
	for(i=0;i<strlen(External_Probe);i++){insertArray(&headerArray,External_Probe[i]);}
	for(i=0;i<strlen(FileVersion);i++){insertArray(&headerArray,FileVersion[i]);}
	for(i=0;i<strlen(Firmware);i++){insertArray(&headerArray,Firmware[i]);}
	for(i=0;i<strlen(FittingType);i++){insertArray(&headerArray,FittingType[i]);}
	for(i=0;i<strlen(FusePSI);i++){insertArray(&headerArray,FusePSI[i]);}
	for(i=0;i<strlen(FuseIFP);i++){insertArray(&headerArray,FuseIFP[i]);}
	for(i=0;i<strlen(FuseLength);i++){insertArray(&headerArray,FuseLength[i]);}
	for(i=0;i<strlen(FusionType);i++){insertArray(&headerArray,FusionType[i]);}
	for(i=0;i<strlen(MaxGraphPSI);i++){insertArray(&headerArray,MaxGraphPSI[i]);}
	for(i=0;i<strlen(MaxGraphTime);i++){insertArray(&headerArray,MaxGraphTime[i]);}
	for(i=0;i<strlen(GraphNumPoints);i++){insertArray(&headerArray,GraphNumPoints[i]);}
	for(i=0;i<strlen(SoakPSI);i++){insertArray(&headerArray,SoakPSI[i]);}
	for(i=0;i<strlen(SoakIFP);i++){insertArray(&headerArray,SoakIFP[i]);}
	for(i=0;i<strlen(SoakLength);i++){insertArray(&headerArray,SoakLength[i]);}
	for(i=0;i<strlen(Heater);i++){insertArray(&headerArray,Heater[i]);}
	for(i=0;i<strlen(Job_No);i++){insertArray(&headerArray,Job_No[i]);}
	for(i=0;i<strlen(Joint_No);i++){insertArray(&headerArray,Joint_No[i]);}
	for(i=0;i<strlen(MachID);i++){insertArray(&headerArray,MachID[i]);}
	for(i=0;i<strlen(MachModel);i++){insertArray(&headerArray,MachModel[i]);}
	for(i=0;i<strlen(MinBead);i++){insertArray(&headerArray,MinBead[i]);}
	for(i=0;i<strlen(Notes);i++){insertArray(&headerArray,Notes[i]);}
	for(i=0;i<strlen(DwellTime);i++){insertArray(&headerArray,DwellTime[i]);}
	for(i=0;i<strlen(Operator);i++){insertArray(&headerArray,Operator[i]);}
	for(i=0;i<strlen(Path_to_graph_data);i++){insertArray(&headerArray,Path_to_graph_data[i]);}
	for(i=0;i<strlen(PipeAngle);i++){insertArray(&headerArray,PipeAngle[i]);}
	for(i=0;i<strlen(PipeMaterial);i++){insertArray(&headerArray,PipeMaterial[i]);}
	for(i=0;i<strlen(PipeSize);i++){insertArray(&headerArray,PipeSize[i]);}
	for(i=0;i<strlen(PistonArea);i++){insertArray(&headerArray,PistonArea[i]);}
	for(i=0;i<strlen(Software);i++){insertArray(&headerArray,Software[i]);}
	for(i=0;i<strlen(Path_to_data_file);i++){insertArray(&headerArray,Path_to_data_file[i]);}
	insertArray(&headerArray,'\0');
	
	return headerArray;
}
//read actions
char *readString(FILE *file,int num_elements){
	
	unsigned char buffer[num_elements];
	fread(buffer,sizeof(buffer),1,file);
	
	char* result=malloc(strlen(buffer)+1);
	//strcpy(result,buffer);
	int i;
	for(i=0;i<=num_elements;i++){
		if(i==num_elements){
			result[i]='\0';
		} else {
			result[i]=buffer[i];
		}
	}
	//result[strlen(result)-1]='\0';
	return result;
}
char *readRawString(FILE *file,int num_elements){
	setlocale(LC_ALL,"en_US.UTF-16");
	
	int i;
	wint_t ch;
	char cleanString[num_elements+1];
	
	for(i=0;i<num_elements;i++){cleanString[i]=fgetwc(file)>>8;}
	
	char* result=malloc(strlen(cleanString)+1);
	for(i=0;i<=num_elements;i++){
		if(i==num_elements){
			result[i]='\0';
		} else {
			result[i]=cleanString[i];
		}
	}

	return result;
}

int readShort(FILE *file){
	uint8_t buffer[2];
	fread(buffer,sizeof(buffer),1,file);
	int swapped=(buffer[1]<<8)|(buffer[0]);

	return swapped;

}

char* readMJRString(FILE *file){
	char* MJRString="";
	
	int len = readShort(file);
	if(len==0){
		readShort(file);
		return MJRString;
	} else {
		
		MJRString=readRawString(file,len);
		char* result=malloc(strlen(MJRString)+1);
		strcpy(result,MJRString);
		return result;
	}
	
}

//will read mjr, dl4, dl5 files
char *dumpbytes(char *file_path){
	FILE *fileptr;
	char *buffer;
	long filelen;

	fileptr = fopen(file_path, "rb");  	  // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
	fread(buffer, filelen, 1, fileptr); // Read in the entire file
	fclose(fileptr);
	return buffer;
}

int get_ftype(char *fpath){
	int i;
	int dotplace;
	for(i=0;i<strlen(fpath);i++){
		if (fpath[i]=='.'){
			dotplace=i;
		}
	}
	
	i=0;
	int fextlen=strlen(fpath)-dotplace+1;
	char fext[fextlen];
	for(i=dotplace;i<strlen(fpath);i++){
		fext[i-dotplace]=fpath[i];

	}
	fext[strlen(fpath)-dotplace]='\0';
	if(strcmp(fext,".mjr")==0){
		return 3;
	}
	else if(strcmp(fext,".dl4")==0){
		return 4;
	}
	else if(strcmp(fext,".dl5")==0){
		return 5;
	}
	else{
		return 0;
	}
}
char* formatPipeSize(char * pBV, int pBT, char * pEV, int pET){
	char* bformat;
	switch(pBT){
		case 1:
			bformat="%s\" DIPS ";
			break;
		case 2:
			bformat="%s\" O.D. ";
			break;
		case 3:
			bformat="%smm O.D. ";
			break;
		case 4:
			bformat="%smm JIS ";
			break;
		default:
			bformat="%s\" IPS ";
	}
	char* eformat;
	switch(pET){
		case 1:
			eformat="%s\" WT";
			break;
		case 2:
			eformat="%smm WT";
			break;
		default:
			eformat="DR %s";
	}
	int blength = snprintf(NULL, 0, bformat, pBV);
	int elength = snprintf(NULL, 0, eformat, pEV);
	++blength;           // +1 for null terminator
	++elength;
	char* BString = malloc(blength);
	char* EString = malloc(elength);
	snprintf(BString, blength, bformat, pBV);
	snprintf(EString, elength, eformat, pEV);
	
	char* PString = malloc(blength+elength-1);
	int i;
	for(i=0;i<blength-1;i++){
		PString[i]=BString[i];
	}
	for(i=0;i<elength;i++){
		PString[i+blength-1]=EString[i];
	}
	
	return PString;
	
}

void add_to_data(Array line){
	int i;
	int last_used_space=data.used;
	insertArray(&data,'\n');
	for(i=0;i<line.used;i++){
		insertArray(&data,line.array[i]);
	}
}

void output_to_csv(Array outputstring){
	char* outputpath="C:/Users/User/Dropbox (ISCO)/Graphomatic 3000/tests/dltestjoint.csv";
	FILE *x=fopen(outputpath,"wb");
	int i;
	for(i=0;i<outputstring.used;i++){
		//putchar(outputstring.array[i]);
		fputc(outputstring.array[i],x);
		//fputc(",",x);
	}
	putchar('\n');
	fclose(x);
}
Array parse_mjr_data(FILE *file, char* fpath,char* spath){
	Array mjrdata;
	int arr_size=3;
	initArray(&mjrdata,(size_t)arr_size);
	//const char ** mjrdata[3];
	
	//File Version
	char* FileVersion = readString(file,10);
	//printf("FileVersion:%s\n",FileVersion);
	
	//Date
	int year=readShort(file);
	int month=readShort(file);
	int day=readShort(file);
	int hour=readShort(file);
	int minute=readShort(file);
	int second=readShort(file);
	char* DateTime=malloc(strlen("%02d/%02d/%02d %02d:%02d:%02d"));
	sprintf(DateTime,"%02d/%02d/%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
	//printf("Joint Date:%s\n",DateTime);
	
	//Machine Info
	char* MachID=readMJRString(file);
	//printf("MachID:%s\n",MachID);
	
	readShort(file);
	char* MachModel=readMJRString(file);
	//printf("MachModel:%s\n",MachModel);
	char* PistonArea=readMJRString(file);
	//printf("PistonArea:%s\n",PistonArea);
	
	//Tracking Info
	readShort(file);
	char* Operator = readMJRString(file);
	//printf("Operator:%s\n",Operator);
	char* Job_No = readMJRString(file);
	//printf("Job_No:%s\n",Job_No);
	
	int jn=readShort(file);
	int jnlength = snprintf(NULL, 0, "%d", jn);
	++jnlength;           // +1 for null terminator
	char* Joint_No = malloc(jnlength);
	snprintf(Joint_No, jnlength, "%d", jn);
	//printf("Joint_No:%s\n",Joint_No);
	
	//Pipe Information
	readShort(file);
	char* PipeMaterial=readMJRString(file);
	char* FittingType;
	char* PipeSize;
	if(strstr(MachModel,"(Sidewinder Mech.)")!=NULL || strstr(MachModel,". SW")!=NULL){
		FittingType=readMJRString(file);
		readShort(file);
		PipeSize=readMJRString(file);
		readShort(file);
	} else {
		FittingType="";
		
		char* pipeSizeBeginValue = readMJRString(file);
		int pipeSizeBeginType = readShort(file);
		char* pipeSizeEndValue = readMJRString(file);
		int pipeSizeEndType = readShort(file);
		
		PipeSize = formatPipeSize(pipeSizeBeginValue,pipeSizeBeginType,pipeSizeEndValue,pipeSizeEndType);
		
	}
	/* printf("Pipe Material:%s\n",PipeMaterial);
	printf("Fitting Type:%s\n",FittingType);
	printf("Pipe Size:%s\n",PipeSize); */
	
	//Pressure Information
	char* BeadIFP = readMJRString(file);
	char* SoakIFP = readMJRString(file);
	char* FuseIFP = readMJRString(file);
	char* CoolIFP = readMJRString(file);
	
	readShort(file);
	
	char* DragPSI = readMJRString(file);
	char* BeadPSI = readMJRString(file);
	char* SoakPSI = readMJRString(file);
	char* FusePSI = readMJRString(file);
	char* CoolPSI = readMJRString(file);
	
	//Temperature Information
	readShort(file);
	char* External_Probe = readMJRString(file);
	char* Datalogger_Probe = readMJRString(file);
	
	//Junk
	int j;
	for(j=0;j<4;j++){
		readShort(file);
	}
	
	//Notes
	char* Notes = readMJRString(file);
	
	readShort(file);
	
	//Datalogger Info
	char* DataloggerInfo = readMJRString(file);
	//printf("Datalogger Info:%s\n",DataloggerInfo);
	char Datalogger_No[4];
	for(j=11;j<15;j++){
		Datalogger_No[j-11] = DataloggerInfo[j];
	}
	
	//-0-Datalogger Software
	int slength = snprintf(NULL, 0, "v.%c.%c.%c", DataloggerInfo[15],DataloggerInfo[16],DataloggerInfo[17]);
	++slength;           // +1 for null terminator
	char* Software = malloc(slength);
	snprintf(Software, slength, "v.%c.%c.%c", DataloggerInfo[15],DataloggerInfo[16],DataloggerInfo[17]);
	
	//-0-Datalogger Calibration Date
	char date1[4];
	char date2[2];
	char date3[2];
	for(j=18;j<22;j++){
		date1[j-18]=DataloggerInfo[j];
	}

	for(j=22;j<24;j++){
		date2[j-22]=DataloggerInfo[j];
	}

	for(j=24;j<26;j++){
		date3[j-24]=DataloggerInfo[j];
	}

	
	int clength = snprintf(NULL, 0, "%s/%s/%s", date1,date2,date3);
	++clength;           // +1 for null terminator
	char* Calibration_Date = malloc(clength);
	snprintf(Software, clength, "%s/%s/%s", date1,date2,date3);
	
	char* y=readMJRString(file);
	
	//printf("%s",y);
	
	char* graphHeader = readString(file,20);
	
	//printf("%s\n",graphHeader);
	
	char GraphMaxPSI_U[5];
	char GraphMaxTime_U[6];
	char GraphNumPoints_U[6];
	
	for(j=2;j<=6;j++){
		GraphMaxPSI_U[j-2]=graphHeader[j];
		if(j==6){
			GraphMaxPSI_U[j-2]='\0';
		} else {
			GraphMaxPSI_U[j-2]=graphHeader[j];
		}
	}
	
	for(j=8;j<=13;j++){
		if(j==13){
			GraphMaxTime_U[j-8]='\0';
		} else {
			GraphMaxTime_U[j-8]=graphHeader[j];
		}
	}
	for(j=15;j<=20;j++){
		if(j==20){
			GraphNumPoints_U[j]='\0';
		} else {
			GraphNumPoints_U[j-15]=graphHeader[j];
		}
	}

	
	char* hold1;
	char* hold2;
	//char* hold3;
	
	double GraphMaxPSI = strtod(GraphMaxPSI_U,&hold1);
	double GraphMaxTime = strtod(GraphMaxTime_U,&hold2)/5.0;
	int GraphNumPoints = atoi(GraphNumPoints_U);
	
	//printf("%f %f %d\n",GraphMaxPSI,GraphMaxTime,GraphNumPoints);

	readString(file,1);

	int graphData[GraphNumPoints][2];

	int k;
	for(k=0;k<GraphNumPoints;k++){

		int t=readShort(file);
		int p=readShort(file);

		graphData[k][0]=t;
		graphData[k][1]=p;
		
		//printf("%04d,%04d\n",t,p);
	}
	
	char* Path_to_data_file=fpath;
	char* Path_to_graph_data=spath;
	
	int i;
	insertArray(&mjrdata,','); //BeadLength
	for(i=0;i<strlen(BeadPSI);i++){insertArray(&mjrdata,BeadPSI[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(BeadIFP);i++){insertArray(&mjrdata,BeadIFP[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(Calibration_Date);i++){insertArray(&mjrdata,Calibration_Date[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,','); //Computer
	for(i=0;i<strlen(CoolPSI);i++){insertArray(&mjrdata,CoolPSI[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(CoolIFP);i++){insertArray(&mjrdata,CoolIFP[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(Datalogger_No);i++){insertArray(&mjrdata,Datalogger_No[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(Datalogger_Probe);i++){insertArray(&mjrdata,Datalogger_Probe[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(DateTime);i++){insertArray(&mjrdata,DateTime[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(DragPSI);i++){insertArray(&mjrdata,DragPSI[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(External_Probe);i++){insertArray(&mjrdata,External_Probe[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(FileVersion);i++){insertArray(&mjrdata,FileVersion[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,','); //Firmware
	for(i=0;i<strlen(FittingType);i++){insertArray(&mjrdata,FittingType[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(FusePSI);i++){insertArray(&mjrdata,FusePSI[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(FuseIFP);i++){insertArray(&mjrdata,FuseIFP[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,',');//FuseLength
	insertArray(&mjrdata,',');//Fusion Type
	insertArray(&mjrdata,GraphMaxPSI);insertArray(&mjrdata,',');
	insertArray(&mjrdata,GraphMaxTime);insertArray(&mjrdata,',');
	insertArray(&mjrdata,GraphNumPoints);insertArray(&mjrdata,',');
	for(i=0;i<strlen(SoakPSI);i++){insertArray(&mjrdata,SoakPSI[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(SoakIFP);i++){insertArray(&mjrdata,SoakIFP[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,','); //SoakLength
	insertArray(&mjrdata,','); //Heater
	for(i=0;i<strlen(Job_No);i++){insertArray(&mjrdata,Job_No[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,'\'');
	for(i=0;i<strlen(Joint_No);i++){insertArray(&mjrdata,Joint_No[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(MachID);i++){insertArray(&mjrdata,MachID[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(MachModel);i++){insertArray(&mjrdata,MachModel[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,',');//MinBead
	for(i=0;i<strlen(Notes);i++){insertArray(&mjrdata,Notes[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,',');//DwellTime
	for(i=0;i<strlen(Operator);i++){insertArray(&mjrdata,Operator[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(Path_to_graph_data);i++){insertArray(&mjrdata,Path_to_graph_data[i]);}insertArray(&mjrdata,',');
	insertArray(&mjrdata,',');//PipeAngle
	for(i=0;i<strlen(PipeMaterial);i++){insertArray(&mjrdata,PipeMaterial[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(PipeSize);i++){insertArray(&mjrdata,PipeSize[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(PistonArea);i++){insertArray(&mjrdata,PistonArea[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(Software);i++){insertArray(&mjrdata,Software[i]);}insertArray(&mjrdata,',');
	for(i=0;i<strlen(Path_to_data_file);i++){insertArray(&mjrdata,Path_to_data_file[i]);}insertArray(&mjrdata,',');

	printArray(mjrdata);
	//printf("%s\n",mjrdata);
	//output_to_csv(mjrdata);
	return mjrdata;
}

Array parse_dl4_data(FILE *file, char* fpath,char* spath){
	Array dl4data;
	return dl4data;
}

Array parse_dl5_data(FILE *file, char* fpath,char* spath){
	return parse_dl4_data(file,fpath,spath);
}

Array get_ordered_data(FILE *file,int ftype, char* fpath,char* spath){
	bsmarker=0;
	if (ftype==3){
		return parse_mjr_data(file,fpath,spath);
	}
	else if (ftype==4){
		return parse_dl4_data(file,fpath,spath);
	}
	else if (ftype==5){
		return parse_dl5_data(file,fpath,spath);
	}
}

// char ** csvify(char * data){
	// char ** resulting_array;
	// int d_i;
	// for(d_i=0;d_i<sizeof(*data)*sizeof(char);d_i++){
		// const char *k="\"%s\",";
		// snprintf(*resulting_array[d_i],,k,*data[d_i]);
	// }
	// return resulting_array;
//}


/* List the files in "dir_name". */

static void list_dir (const char * dir_name)
{
    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
	printf ("%s/%s\n", dir_name, d_name);

// #if 0
	// /* If you don't want to print the directories, use the
	   // following line: */

        // if (! (entry->d_type & DT_DIR)) {
	    // printf ("%s/%s\n", dir_name, d_name);
	// }

// #endif /* 0 */


        // if (entry->d_type & DT_DIR) {

            // /* Check that the directory is not "d" or d's parent. */
            
            // if (strcmp (d_name, "..") != 0 &&
                // strcmp (d_name, ".") != 0) {
                // int path_length;
                // char path[PATH_MAX];
 
                // path_length = snprintf (path, PATH_MAX,
                                        // "%s/%s", dir_name, d_name);
                // printf ("%s\n", path);
                // if (path_length >= PATH_MAX) {
                    // fprintf (stderr, "Path length has got too long.\n");
                    // exit (EXIT_FAILURE);
                // }
                // /* Recursively call "list_dir" with the new path. */
                // list_dir (path);
            // }
	// }
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
}


char* convert_to_csv_path(char* folderPath, char* dlpath){
	int i;

	char* gDPath=strcat(folderPath,"graphData/");

	Array upToFolderMatchA;
	initArray(&upToFolderMatchA,5);
	int match_i;
	for(i=0;i<strlen(dlpath);i++){

		insertArray(&upToFolderMatchA,dlpath[i]);

		if(strcmp(upToFolderMatchA.array,folderPath)==0){
			match_i=i;
			break;
		}
	}
	
	printf("got here 3");
	char* afterFolderMatch;
	for(i=match_i;i<strlen(strchr(dlpath,'.'));i++){
		afterFolderMatch[i-match_i]=dlpath[i];
	}
	printf("got here 4");
	// int last_slash=strchr(dlpath,"/");
	// char* upToLastSlash;
	// for(i=0;i<last_slash;i++){
		// upToLastSlash[i]=dlpath[i];
	// }
	
	// char* afterLastSlash;
	// for(i=last_slash;i<strchr(dlpath,".");i++){
		// afterLastSlash[i]=dlpath[i];
	//}
	printf("got here 5");
	char* csvPath=strcat(afterFolderMatch,".csv");
	printf("got here 6");
	char* resultingPath=strcat(upToFolderMatch,csvPath);
	printf("got here 7");
	char* rPath=malloc(sizeof(resultingPath));
	
	return rPath;
	
	
}

//idea is to have a stream of actions that occur based on hand-determined order, that place the value into the correct header
//through a function of the sort place_val(value,header,bytestreamreadingfunction)
int main(int argc, char* argv[]){
	
	char* folder = argv[1];
	//overall
	Array comboheaders=constructSummaryHeaders();
	
	initArray(&data,(size_t)5);
	add_to_data(comboheaders);
	printArray(comboheaders);
	Array singulardata;
	
	list_dir(folder);

	//per joint
	char ftype;
	char *fpath = "C:/Users/User/Dropbox (ISCO)/Graphomatic 3000/tests/dltestjoint.mjr";
	char *spath = convert_to_csv_path(folder,fpath);
	
	ftype=get_ftype(fpath);
	FILE *fileptr=fopen(fpath,"rb");
	
	singulardata=get_ordered_data(fileptr,ftype,fpath,spath);
	add_to_data(singulardata);
	printf("got here");
	
	//after
	output_to_csv(data);
	//printArray(data);
}
