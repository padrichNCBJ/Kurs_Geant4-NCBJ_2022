//
// DetectorConstruction.cc 
//

#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"

#include "G4NistManager.hh"
#include "G4GeometryManager.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
fMessenger(this),
// World:
  solidWorld(0),
  logicWorld(0),
  physWorld(0),
  World_Material(0)
{
  BuildMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::BuildMaterials()
{
  // Get nist material manager
  nist = G4NistManager::Instance();

  // Przyklad 1. 
  // Uzywamy gotowy material z bazy:
  woda = nist->FindOrBuildMaterial("G4_WATER");


  // Przyklad 2. 
  // Skladamy nasz wlasny material jako mieszanine pojedynczych pierwiastkow wg. udzialu masowego.
  // Budujemy materiał RW3 (polystyrene with titanium oxide admixture -> https://www.lap-laser.com/products/easy-slab/)
  // Dane o składzie z https://ro.uow.edu.au/cgi/viewcontent.cgi?referer=&httpsredir=1&article=1631&context=eispapers1
  // M. Cameron, et al., "Comparison of phantom materials for use in quality assurance of microbeam radiation therapy microbeam radiation therapy", J. Synchrotron Rad. (2017). 24, 866-876, https://doi.org/10.1107/S1600577517005641
  //
  // Density 1.045 g/cm3
  // Element  Material fraction by weight
  //  H           0.0759
  //  C           0.9041
  //  O           0.008
  //  Ti          0.012
  // Potrzebne pierwiastki bierzemy z bazy NIST:
  G4Element* Hydrogen = nist->FindOrBuildElement("H");
  G4Element* Carbon = nist->FindOrBuildElement("C");
  G4Element* Oxygen = nist->FindOrBuildElement("O");
  G4Element* Titanium = nist->FindOrBuildElement("Ti");
  // Compound: composition by fraction of mass
  G4double RW3_density = 1.045 * g / cm3;
  G4int nComponents = 4;
  RW3 = new G4Material("RW3", RW3_density, nComponents, kStateSolid);
  RW3->AddElement(Hydrogen, 0.0759);
  RW3->AddElement(Carbon, 0.9041);
  RW3->AddElement(Oxygen, 0.008);
  RW3->AddElement(Titanium, 0.012);

  // Przyklad 3. 
  // Budujemy material typu rozrzedzone powietrze na bazie standardowego materialu G4_AIR
  G4Material* Air_STD = nist->FindOrBuildMaterial("G4_AIR");
  G4double temperature = 293.15*kelvin;
  // Gestosc rozrzedzonego powietrza wyliczmy ze wzoru: 
  // rho = p*M / RT
  // rho - gestosc [kg/m3]
  // p - cisnienie [Pa = N/m2]
  // M - efektywna masa molowa powietrza = 0.02897 [kg/mol]
  // R - uniwersalna stala gazowa = 8.3144598 [J/(mol*K) = N*m/(mol*K)]
  // T - temperatura w skali bezwzglednej [K]
  // 1 Atm = 1.01325E5 Pa = 760 Torr
  // Gestosc dla roznych cisnien:
  // 1E-2 Torr:
  //  G4double pressure = 1.33322368421053*pascal;
  //  G4double density = 1.58462892465068E-05*kg/m3;
  // 1E-3 Torr:
  //  G4double pressure = 0.133322368421053*pascal;
  //  G4double density = 1.58462892465068E-06*kg/m3;
  // 1E-4 Torr:
  G4double pressure = 0.013332236842105 * pascal;
  G4double density = 1.58462892465068E-07 * kg / m3;
  Air_low_pressure = new G4Material("Air_low_pressure", density, Air_STD, kStateGas, temperature, pressure);

  // Przyklad 4.
  // Budujemy material modelujacy glebe.
  // Skład gleby wg. Martin E. Keillor et al., Streamlined Monte Carlo simulation of
  //  environmental gamma-ray backgrounds for radiation detector sensitivity comparisons,
  //  Journal of Radioanalytical and Nuclear Chemistry (2018) 318:485–490; 
  //  https://doi.org/10.1007/s10967-018-6150-4
  // U.S. Average Earth was defined with a density of 1.52 g/cm3, 
  // and composed of elements with the following weight fractions: 
  // O (0.513713), 
  // Si (0.271183), 
  // Al (0.068563), 
  // Fe (0.056283), 
  // Ca (0.051167), 
  // K (0.014327), 
  // Mg (0.013303),
  // Na (0.006140), 
  // Ti (0.004605), and 
  // Mn (0.000716).
  G4double O_wfrac  = 0.513713 ;
  G4double Si_wfrac = 0.271183 ;
  G4double Al_wfrac = 0.068563 ;
  G4double Fe_wfrac = 0.056283 ;
  G4double Ca_wfrac = 0.051167 ;
  G4double K_wfrac = 0.014327 ;
  G4double Mg_wfrac = 0.013303 ;
  G4double Na_wfrac = 0.006140 ;
  G4double Ti_wfrac = 0.004605 ;
  G4double Mn_wfrac = 0.000716 ;
  G4int Soil_Ncomponents = 10;
  G4double Soil_density = 1.52*g/cm3;
  G4Material* O = nist->FindOrBuildMaterial("G4_O");  // Tlen
  G4Material* Si = nist->FindOrBuildMaterial("G4_Si");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Fe = nist->FindOrBuildMaterial("G4_Fe");
  G4Material* Ca = nist->FindOrBuildMaterial("G4_Ca");
  G4Material* K = nist->FindOrBuildMaterial("G4_K");
  G4Material* Mg = nist->FindOrBuildMaterial("G4_Mg");
  G4Material* Na = nist->FindOrBuildMaterial("G4_Na");
  G4Material* Ti = nist->FindOrBuildMaterial("G4_Ti");
  G4Material* Mn = nist->FindOrBuildMaterial("G4_Mn");
  G4double fractionmass;
  Soil_Material = new G4Material("Soil",Soil_density, Soil_Ncomponents);
  Soil_Material->AddMaterial(O, fractionmass=O_wfrac);
  Soil_Material->AddMaterial(Si,fractionmass=Si_wfrac);
  Soil_Material->AddMaterial(Al,fractionmass=Al_wfrac);
  Soil_Material->AddMaterial(Fe,fractionmass=Fe_wfrac);
  Soil_Material->AddMaterial(Ca,fractionmass=Ca_wfrac);
  Soil_Material->AddMaterial(K,fractionmass=K_wfrac);
  Soil_Material->AddMaterial(Mg,fractionmass=Mg_wfrac);
  Soil_Material->AddMaterial(Na,fractionmass=Na_wfrac);
  Soil_Material->AddMaterial(Ti,fractionmass=Ti_wfrac);
  Soil_Material->AddMaterial(Mn,fractionmass=Mn_wfrac);
}

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
  World_Material = woda;
  World_Material = Air_low_pressure;
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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetWorldMaterial(G4String newMaterial)
{ 
  World_Material = nist->FindOrBuildMaterial(newMaterial);
  if (logicWorld != 0 ) {
    G4GeometryManager::GetInstance()->OpenGeometry();
    logicWorld->SetMaterial(World_Material);
    G4RunManager::GetRunManager()->GeometryHasBeenModified(); 
  }	
}