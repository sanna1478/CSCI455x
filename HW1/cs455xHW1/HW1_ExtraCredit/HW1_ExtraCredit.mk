##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=HW1_ExtraCredit
ConfigurationName      :=Debug
WorkspacePath          :=/home/ash/CS455x/HW1/cs455xHW1
ProjectPath            :=/home/ash/CS455x/HW1/cs455xHW1/HW1_ExtraCredit
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=ash
Date                   :=28/05/18
CodeLitePath           :=/home/ash/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="HW1_ExtraCredit.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(ObjectSuffix): ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp $(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/ash/CS455x/HW1/cs455xHW1/HW1_ExtraCredit/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(DependSuffix): ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(DependSuffix) -MM ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp

$(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(PreprocessSuffix): ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp$(PreprocessSuffix) ShreyashAnnapureddy_1072336621_HW1_ExtraCredit.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


