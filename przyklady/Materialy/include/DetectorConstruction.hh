//
// DetectorConstruction.hh 


#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
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
    void BuildMaterials();
    void SetWorldMaterial(G4String newMaterial);


  private:
    DetectorConstructionMessenger fMessenger;
    G4NistManager* nist;
    // World:
    G4Box* solidWorld;
    G4LogicalVolume* logicWorld;
    G4VPhysicalVolume* physWorld;
    G4Material* World_Material;
     G4Material* woda;
    G4Material* RW3;
    G4Material* Air_low_pressure;
    G4Material* Soil_Material;
};

#endif

