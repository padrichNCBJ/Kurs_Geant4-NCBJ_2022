//
// DetectorConstruction.hh 


#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4NistManager.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Box;


/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    void ConstructSDandField();

  private:
    G4NistManager* nist;
    // World:
    G4Box* solidWorld;
    G4LogicalVolume* logicWorld;
    G4VPhysicalVolume* physWorld;
    G4Material* World_Material;
};

#endif

