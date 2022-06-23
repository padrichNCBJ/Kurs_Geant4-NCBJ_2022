// DetectorConstruction Messenger class

#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
// #include "G4UIcmdWithADoubleAndUnit.hh"
// #include "G4UIcmdWithoutParameter.hh"
// #include "G4UIcmdWithAnInteger.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* DetectorConstruction) : G4UImessenger(),
	fDetectorConstruction(DetectorConstruction),
	fTopDirectory(0)
{
	fTopDirectory = new G4UIdirectory("/Detektor/");
	fTopDirectory->SetGuidance("My UI commands specific to the experimental Setup (DetectorConstruction in Geant nomenclature)");

	fSetWorldMaterialCmd = new G4UIcmdWithAString("/Detektor/setWorldMaterial", this);
	fSetWorldMaterialCmd->SetGuidance("Select material for the World");
	fSetWorldMaterialCmd->SetParameterName("WorldMaterial", true);
	fSetWorldMaterialCmd->SetCandidates("G4_Galactic G4_He G4_AIR G4_WATER RW3 Air_low_pressure Soil");
	fSetWorldMaterialCmd->SetDefaultValue("G4_AIR");
	fSetWorldMaterialCmd->AvailableForStates(G4State_Idle);
}

DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
    delete fTopDirectory;
    delete fSetWorldMaterialCmd;
    
}

void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if( command == fSetWorldMaterialCmd ) { 
    fDetectorConstruction->SetWorldMaterial(newValue);
  }
}


