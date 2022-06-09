//
// DetectorConstruction.cc 
//

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
// World:
  solidWorld(0),
  logicWorld(0),
  physWorld(0),
  World_Material(0)
{
  // Get nist material manager
  nist = G4NistManager::Instance();
  World_Material = nist->FindOrBuildMaterial("G4_WATER");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_size_X = 10*cm;
  G4double world_size_Y = 10*cm;
  G4double world_size_Z = 10*cm;
  solidWorld = new G4Box("World", 0.5*world_size_X, 0.5*world_size_Y, 0.5*world_size_Z); 
  logicWorld = new G4LogicalVolume(solidWorld, World_Material, "World");
  physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps); 

  //
  //always return the physical World
  //
  return physWorld;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{}

