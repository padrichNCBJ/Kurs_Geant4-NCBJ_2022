// Mikro aplikacja Geant4

// Obowiazkowe skladowe
#include "G4RunManager.hh"
#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

// Interfejs uzytkownika
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"



int main(int argc,char** argv)
{

  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

  // Run Manager:
  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction:
  runManager->SetUserInitialization(new DetectorConstruction());

  // Physics list:
  G4VModularPhysicsList* physicsList = new FTFP_BERT; 
  runManager->SetUserInitialization(physicsList);

  // User action initialization:
  runManager->SetUserInitialization(new ActionInitialization());

  // Initialize G4 kernel
  //
  runManager->Initialize();
  

  // User interface:
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  

  delete visManager;
  delete runManager;

  return 0;
}

