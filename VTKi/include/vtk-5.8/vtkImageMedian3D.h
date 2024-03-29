/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkImageMedian3D.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImageMedian3D - Median Filter
// .SECTION Description
// vtkImageMedian3D a Median filter that replaces each pixel with the 
// median value from a rectangular neighborhood around that pixel.
// Neighborhoods can be no more than 3 dimensional.  Setting one
// axis of the neighborhood kernelSize to 1 changes the filter
// into a 2D median.  


#ifndef __vtkImageMedian3D_h
#define __vtkImageMedian3D_h


#include "vtkImageSpatialAlgorithm.h"

class VTK_IMAGING_EXPORT vtkImageMedian3D : public vtkImageSpatialAlgorithm
{
public:
  static vtkImageMedian3D *New();
  vtkTypeMacro(vtkImageMedian3D,vtkImageSpatialAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // This method sets the size of the neighborhood.  It also sets the 
  // default middle of the neighborhood 
  void SetKernelSize(int size0, int size1, int size2);

  // Description:
  // Return the number of elements in the median mask
  vtkGetMacro(NumberOfElements,int);

protected:
  vtkImageMedian3D();
  ~vtkImageMedian3D();

  int NumberOfElements;

  void ThreadedRequestData(vtkInformation *request,
                           vtkInformationVector **inputVector,
                           vtkInformationVector *outputVector,
                           vtkImageData ***inData, vtkImageData **outData, 
                           int extent[6], int id);

private:
  vtkImageMedian3D(const vtkImageMedian3D&);  // Not implemented.
  void operator=(const vtkImageMedian3D&);  // Not implemented.
};

#endif
