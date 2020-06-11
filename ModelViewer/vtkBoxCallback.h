#ifndef VTKBOXCALLBACK_H_INCLUDED
#define VTKBOXCALLBACK_H_INCLUDED
// To call back for box widget

/** @file
 * This file contains the declarations for the vtkBoxCallback class to be used for Box Widget
 */

#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkBoxWidget2.h>
#include <vtkTransform.h>
#include <vtkBoxRepresentation.h>

// Create vtkBoxCallback class which inherits the vtkCommand class
class vtkBoxCallback : public vtkCommand
{
public:
    /** Constructor for vtkBoxCallback
     */
    vtkBoxCallback();
    /** To create a new instance of vtkBoxCallback
     */
    static vtkBoxCallback* New();

    vtkSmartPointer<vtkActor> m_actor; /**< Stores the actor to be transformed */
    /** Sets the actor to be transformed via the box widget
     * @param actor Sets the actor to be used for the box widget
     */
    void SetActor(vtkSmartPointer<vtkActor> actor);
    /** Execute box widget transformation on the m_actor
     */
    virtual void Execute(vtkObject* caller, unsigned long, void*);

};
#endif // VTKBOXCALLBACK_H_INCLUDED
