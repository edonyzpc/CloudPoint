/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRectilinearGridClip.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkRectilinearGridClip - Reduces the image extent of the input.
// .SECTION Description
// vtkRectilinearGridClip  will make an image smaller.  The output must have
// an image extent which is the subset of the input.  The filter has two 
// modes of operation: 
// 1: By default, the data is not copied in this filter. 
// Only the whole extent is modified.  
// 2: If ClipDataOn is set, then you will get no more that the clipped
// extent.
#ifndef __vtkRectilinearGridClip_h
#define __vtkRectilinearGridClip_h

// I did not make this a subclass of in place filter because
// the references on the data do not matter. I make no modifications
// to the data.
#include "vtkRectilinearGridAlgorithm.h"

class VTK_GRAPHICS_EXPORT vtkRectilinearGridClip : public vtkRectilinearGridAlgorithm
{
public:
  static vtkRectilinearGridClip *New();
  vtkTypeMacro(vtkRectilinearGridClip,vtkRectilinearGridAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // The whole extent of the output has to be set explicitly.
  void SetOutputWholeExtent(int extent[6], vtkInformation *outInfo=0);
  void SetOutputWholeExtent(int minX, int maxX, int minY, int maxY, 
                            int minZ, int maxZ);
  void GetOutputWholeExtent(int extent[6]);
  int *GetOutputWholeExtent() {return this->OutputWholeExtent;}

  void ResetOutputWholeExtent();

  // Description:
  // By default, ClipData is off, and only the WholeExtent is modified.
  // the data's extent may actually be larger.  When this flag is on,
  // the data extent will be no more than the OutputWholeExtent.
  vtkSetMacro(ClipData, int);
  vtkGetMacro(ClipData, int);
  vtkBooleanMacro(ClipData, int);

  // Description:
  // Hack set output by piece
  void SetOutputWholeExtent(int piece, int numPieces);

protected:
  vtkRectilinearGridClip();
  ~vtkRectilinearGridClip() {};

  // Time when OutputImageExtent was computed.
  vtkTimeStamp CTime;
  int Initialized; // Set the OutputImageExtent for the first time.
  int OutputWholeExtent[6];

  int ClipData;
  
  virtual int RequestInformation (vtkInformation *,
                                  vtkInformationVector **,
                                  vtkInformationVector *);

  void CopyData(vtkRectilinearGrid *inData, vtkRectilinearGrid *outData, int *ext);

  virtual int RequestData(vtkInformation *,
                          vtkInformationVector **,
                          vtkInformationVector *);

private:
  vtkRectilinearGridClip(const vtkRectilinearGridClip&);  // Not implemented.
  void operator=(const vtkRectilinearGridClip&);  // Not implemented.
};



#endif



