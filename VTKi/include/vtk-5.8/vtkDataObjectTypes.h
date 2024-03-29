/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDataObjectTypes.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDataObject - helper class to get VTK data object types as string and instantiate them
// .SECTION Description
// vtkDataObjectTypes is a helper class that supports conversion between
// integer types defined in vtkType.h and string names as well as creation
// of data objects from either integer or string types. This class has
// to be updated every time a new data type is added to VTK.
// .SECTION See Also
// vtkDataObject

#ifndef __vtkDataObjectTypes_h
#define __vtkDataObjectTypes_h

#include "vtkObject.h"

class vtkDataObject;

class VTK_FILTERING_EXPORT vtkDataObjectTypes : public vtkObject
{
public:
  static vtkDataObjectTypes *New();

  vtkTypeMacro(vtkDataObjectTypes,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Given an int (as defined in vtkType.h) identifier for a class
  // return it's classname.
  static const char* GetClassNameFromTypeId(int typeId);

  // Description:
  // Given a data object classname, return it's int identified (as
  // defined in vtkType.h)
  static int GetTypeIdFromClassName(const char* classname);

  // Description:
  // Create (New) and return a data object of the given classname.
  static vtkDataObject* NewDataObject(const char* classname);

  // Description:
  // Create (New) and return a data object of the given type id.
  static vtkDataObject* NewDataObject(int typeId);

protected:
  vtkDataObjectTypes() {};
  ~vtkDataObjectTypes() {};

private:
  vtkDataObjectTypes(const vtkDataObjectTypes&);  // Not implemented.
  void operator=(const vtkDataObjectTypes&);  // Not implemented.
};

#endif

