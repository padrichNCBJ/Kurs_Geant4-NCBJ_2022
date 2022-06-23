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
class G4Tubs;
class G4VisAttributes;


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
    void ConstructPhantom();


  private:
    DetectorConstructionMessenger fMessenger;
    G4NistManager* nist;
    // World:
    G4Box* fSolidWorld;
    G4LogicalVolume* fLogicWorld;
    G4VPhysicalVolume* fPhysWorld;
    G4Material* fWorldMaterial;
    G4Tubs* fSolidTank;
    G4LogicalVolume* fLogicTank; 
    G4VPhysicalVolume* fPhysTank; 
    G4Material* fPhantomMaterial;
    G4Material* fWoda;
    G4Material* fRW3;
    G4Material* fAirLowPressure;
    G4Material* fSoilMaterial;
    // Atrybuty wizualizacji
    std::vector<G4VisAttributes*> fVisAttributes;

};

#endif

