// Mikro aplikacja Geant4

// Obowiazkowe skladowe
#include "G4RunManager.hh"
#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"


//#include "G4EmLivermorePhysics.hh"
//#include "G4EmParameters.hh"
//#include "G4ProductionCutsTable.hh"
//#include "G4SystemOfUnits.hh"

// Interfejs uzytkownika
#include "G4UImanager.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif



int main(int argc,char** argv)
{
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
  
#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
    UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
    if (ui->IsGUI())
        UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

