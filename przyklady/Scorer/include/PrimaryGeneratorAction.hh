// Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

// The primary generator action class with general particle source.
//
// The default is a 6 MeV electron, point source at (0.,0.,0.) 
// with direction vector (0.,0.,1.)

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    G4GeneralParticleSource* GetGeneralParticleSource() { return fGeneralParticleSource; }

  private:
    G4GeneralParticleSource*  fGeneralParticleSource; // pointer a to G4 general particel source class
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


