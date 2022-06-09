//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm14/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
// $Id: RunAction.cc 68313 2013-03-21 18:15:21Z maire $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "G4AnalysisManager.hh"
//#include "g4root.hh"

#include "G4Run.hh"
#include "globals.hh"
#include "G4RunManager.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  auto AnalysisManager = G4AnalysisManager::Instance();
  AnalysisManager->SetVerboseLevel(1);
  AnalysisManager->SetNtupleMerging(true);

 // Creating ntuple
 
  AnalysisManager->CreateNtuple("Generator", "Charakterystyka czastki pierwotnej");
  AnalysisManager->CreateNtupleIColumn("PDG");  // IColumn to store integers
  AnalysisManager->CreateNtupleDColumn("Ekin");  // DColumn to store Doubles
  AnalysisManager->CreateNtupleDColumn("x");
  AnalysisManager->CreateNtupleDColumn("y");
  AnalysisManager->CreateNtupleDColumn("z");
  AnalysisManager->CreateNtupleDColumn("px");
  AnalysisManager->CreateNtupleDColumn("py");
  AnalysisManager->CreateNtupleDColumn("pz");  
  AnalysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{  
  auto AnalysisManager = G4AnalysisManager::Instance();
  G4String fileName = "Generator_Test.root";
  AnalysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  auto AnalysisManager = G4AnalysisManager::Instance();
  AnalysisManager->Write();
  AnalysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
