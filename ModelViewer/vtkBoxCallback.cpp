// To call back for box widget
#include <vtkBoxCallback.h>

/** @file
 * This file contains the code for the vtkBoxCallback class to be used for Box Widget
 */

// constructor
vtkBoxCallback::vtkBoxCallback() {}


// Create new instance of call back
vtkBoxCallback* vtkBoxCallback::New()
{
    return new vtkBoxCallback;
}

// Set the actor, inputted from the mainwindow's actor variable
void vtkBoxCallback::SetActor(vtkSmartPointer<vtkActor> actor)
{
    m_actor = actor;
}

// Execute box widget
void vtkBoxCallback::Execute(vtkObject* caller, unsigned long, void*)
{
    vtkSmartPointer<vtkBoxWidget2> boxWidget =
        dynamic_cast<vtkBoxWidget2*>(caller);

    vtkSmartPointer<vtkTransform> t =
        vtkSmartPointer<vtkTransform>::New();

    dynamic_cast<vtkBoxRepresentation*>(boxWidget->GetRepresentation())->GetTransform(t); // Get box widget bounds
    this->m_actor->SetUserTransform(t); // Transform actor to box widget's bounds
}
