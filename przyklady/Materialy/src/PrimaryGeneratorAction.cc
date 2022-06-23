// Najprostrza implementacja źródła na bazie Geant4 General Particle Source
//Geant4 General Particle Source


#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4AnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fGeneralParticleSource(0) 
{

  fGeneralParticleSource  = new G4GeneralParticleSource();
  // default particle kinematic (actual set via macro commands at run time)
  /*
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fGeneralParticleSource->SetParticleDefinition(particle);
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fGeneralParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event.

  if (anEvent->GetEventID() == 0 ) G4cout << "Przed wywolaniem GeneratePrimaryVertex. Event ma teraz: " << anEvent->GetNumberOfPrimaryVertex() << " primary vertexow" << G4endl;

  fGeneralParticleSource->GeneratePrimaryVertex(anEvent);

  if (anEvent->GetEventID() == 0 ) G4cout << "Po wywolaniu GeneratePrimaryVertex. Event ma teraz: " << anEvent->GetNumberOfPrimaryVertex() << " primary vertexow" << G4endl;

  const G4PrimaryVertex* PrimaryVertex = anEvent->GetPrimaryVertex(0);
  const G4PrimaryParticle* PrimaryParticle = PrimaryVertex->GetPrimary(0);
  
  if (0) {
    G4cout << "PrimaryVertex =  " << PrimaryVertex << "   PrimaryParticle = " << PrimaryParticle << G4endl;
    G4cout << " PrimaryParticle->GetPDGcode() = " << PrimaryParticle->GetPDGcode() << G4endl;
    G4cout << " PrimaryParticle->GetKineticEnergy() = " << PrimaryParticle->GetKineticEnergy() << G4endl;
    G4cout << " PrimaryVertex->GetX0() = " << PrimaryVertex->GetX0() << G4endl;
    G4cout << " PrimaryParticle->GetPx() = " << PrimaryParticle->GetPx() << G4endl;
    G4cout << " PrimaryParticle->GetPz() = " << PrimaryParticle->GetPz() << G4endl;
  }

  if (PrimaryVertex && PrimaryParticle) {
    auto AnalysisManager = G4AnalysisManager::Instance();
    // fill ntuple
    AnalysisManager->FillNtupleIColumn(0, PrimaryParticle->GetPDGcode());
    AnalysisManager->FillNtupleDColumn(1, PrimaryParticle->GetKineticEnergy());
    AnalysisManager->FillNtupleDColumn(2, PrimaryVertex->GetX0());
    AnalysisManager->FillNtupleDColumn(3, PrimaryVertex->GetY0());
    AnalysisManager->FillNtupleDColumn(4, PrimaryVertex->GetZ0());
    AnalysisManager->FillNtupleDColumn(5, PrimaryParticle->GetPx());
    AnalysisManager->FillNtupleDColumn(6, PrimaryParticle->GetPy());
    AnalysisManager->FillNtupleDColumn(7, PrimaryParticle->GetPz());
    AnalysisManager->AddNtupleRow();
  }
}


