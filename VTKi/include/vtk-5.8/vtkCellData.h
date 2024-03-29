/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCellData.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCellData - represent and manipulate cell attribute data
// .SECTION Description
// vtkCellData is a class that is used to represent and manipulate
// cell attribute data (e.g., scalars, vectors, normals, texture 
// coordinates, etc.) Special methods are provided to work with filter
// objects, such as passing data through filter, copying data from one 
// cell to another, and interpolating data given cell interpolation weights.

#ifndef __vtkCellData_h
#define __vtkCellData_h

#include "vtkDataSetAttributes.h"

class VTK_FILTERING_EXPORT vtkCellData : public vtkDataSetAttributes
{
public:
  static vtkCellData *New();

  vtkTypeMacro(vtkCellData,vtkDataSetAttributes);
  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkCellData() {}; //make sure constructor and desctructor are protected
  ~vtkCellData() {};

private:
  vtkCellData(const vtkCellData&);  // Not implemented.
  void operator=(const vtkCellData&);  // Not implemented.
};

#endif



