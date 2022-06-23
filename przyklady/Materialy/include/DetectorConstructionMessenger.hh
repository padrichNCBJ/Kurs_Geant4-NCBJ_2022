// Messenger class that defines commands for DetectorConstruction 
// (based on /examples/extended/common/detectorConstruction)

#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
// class G4UIcmdWithADoubleAndUnit;
//class G4UIcmdWithoutParameter;
//class G4UIcmdWithAnInteger;

class DetectorConstructionMessenger: public G4UImessenger
{
  public:
	DetectorConstructionMessenger(DetectorConstruction* );
	virtual ~DetectorConstructionMessenger();
	virtual void SetNewValue(G4UIcommand* command, G4String newValue);

  private:
	DetectorConstruction* fDetectorConstruction;
	G4UIdirectory* fTopDirectory;
	G4UIcmdWithAString* fSetWorldMaterialCmd;
};

#endif


