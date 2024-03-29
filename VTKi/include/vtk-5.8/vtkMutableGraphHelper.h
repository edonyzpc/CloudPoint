/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMutableGraphHelper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*----------------------------------------------------------------------------
 Copyright (c) Sandia Corporation
 See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.
----------------------------------------------------------------------------*/
// .NAME vtkMutableGraphHelper - Helper class for building a directed or
//   directed graph
//
// .SECTION Description
// vtkMutableGraphHelper has helper methods AddVertex and AddEdge which
// add vertices/edges to the underlying mutable graph. This is helpful in
// filters which need to (re)construct graphs which may be either directed
// or undirected.
//
// .SECTION See Also
// vtkGraph vtkMutableDirectedGraph vtkMutableUndirectedGraph

#ifndef __vtkMutableGraphHelper_h
#define __vtkMutableGraphHelper_h

#include "vtkObject.h"
#include "vtkGraph.h" // For vtkEdgeType

class vtkDataSetAttributes;
class vtkGraph;
class vtkGraphEdge;
class vtkMutableDirectedGraph;
class vtkMutableUndirectedGraph;

class VTK_INFOVIS_EXPORT vtkMutableGraphHelper : public vtkObject
{
public:
  static vtkMutableGraphHelper *New();
  vtkTypeMacro(vtkMutableGraphHelper, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the underlying graph that you want to modify with this helper.
  // The graph must be an instance of vtkMutableDirectedGraph or
  // vtkMutableUndirectedGraph.
  void SetGraph(vtkGraph* g);
  vtkGraph* GetGraph();

//BTX
  // Description:
  // Add an edge to the underlying mutable graph.
  vtkEdgeType AddEdge(vtkIdType u, vtkIdType v);
//ETX
  vtkGraphEdge* AddGraphEdge(vtkIdType u, vtkIdType v);

  // Description:
  // Add a vertex to the underlying mutable graph.
  vtkIdType AddVertex();

  // Description:
  // Remove a vertex from the underlying mutable graph.
  void RemoveVertex(vtkIdType v);

  // Description:
  // Remove a collection of vertices from the underlying mutable graph.
  void RemoveVertices(vtkIdTypeArray* verts);

  // Description:
  // Remove an edge from the underlying mutable graph.
  void RemoveEdge(vtkIdType e);

  // Description:
  // Remove a collection of edges from the underlying mutable graph.
  void RemoveEdges(vtkIdTypeArray* edges);

protected:
  vtkMutableGraphHelper();
  ~vtkMutableGraphHelper();

  vtkGetObjectMacro(InternalGraph, vtkGraph);
  void SetInternalGraph(vtkGraph* g);
  vtkGraph* InternalGraph;

  vtkGraphEdge* GraphEdge;

  vtkMutableDirectedGraph* DirectedGraph;
  vtkMutableUndirectedGraph* UndirectedGraph;

private:
  vtkMutableGraphHelper(const vtkMutableGraphHelper&);  // Not implemented.
  void operator=(const vtkMutableGraphHelper&);  // Not implemented.
};

#endif
