/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPlot.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkPlot - Abstract class for 2D plots.
//
// .SECTION Description
// The base class for all plot types used in vtkChart derived charts.
//
// .SECTION See Also
// vtkPlotPoints vtkPlotLine vtkPlotBar vtkChart vtkChartXY

#ifndef __vtkPlot_h
#define __vtkPlot_h

#include "vtkContextItem.h"
#include "vtkStdString.h" // Needed to hold TooltipLabelFormat ivar
#include "vtkSmartPointer.h"  // Needed to hold SP ivars

class vtkVariant;
class vtkTable;
class vtkIdTypeArray;
class vtkContextMapper2D;
class vtkPen;
class vtkBrush;
class vtkAxis;
class vtkVector2f;
class vtkRectf;
class vtkStringArray;

class VTK_CHARTS_EXPORT vtkPlot : public vtkContextItem
{
public:
  vtkTypeMacro(vtkPlot, vtkContextItem);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  // Description:
  // Paint legend event for the plot, called whenever the legend needs the
  // plot items symbol/mark/line drawn. A rect is supplied with the lower left
  // corner of the rect (elements 0 and 1) and with width x height (elements 2
  // and 3). The plot can choose how to fill the space supplied. The index is used
  // by Plots that return more than one label.
  virtual bool PaintLegend(vtkContext2D *painter, const vtkRectf& rect,
                           int legendIndex);

  // Description:
  // Sets/gets a printf-style string to build custom tooltip labels from.
  // An empty string generates the default tooltip labels.
  // The following case-sensitive format tags (without quotes) are recognized:
  //   '%x' The X value of the plot element
  //   '%y' The Y value of the plot element
  //   '%i' The IndexedLabels entry for the plot element
  //   '%l' The value of the plot's GetLabel() function
  //   '%s' (vtkPlotBar only) The Labels entry for the bar segment
  // Any other characters or unrecognized format tags are printed in the
  // tooltip label verbatim.
  virtual void SetTooltipLabelFormat(const vtkStdString &label);
  virtual vtkStdString GetTooltipLabelFormat();

//BTX
  // Description:
  // Generate and return the tooltip label string for this plot
  // The segmentIndex parameter is ignored, except for vtkPlotBar
  virtual vtkStdString GetTooltipLabel(const vtkVector2f &plotPos,
                                       vtkIdType seriesIndex,
                                       vtkIdType segmentIndex);

  // Description:
  // Function to query a plot for the nearest point to the specified coordinate.
  // Returns the index of the data series with which the point is associated, or
  // -1 if no point was found.
  virtual vtkIdType GetNearestPoint(const vtkVector2f& point,
                                    const vtkVector2f& tolerance,
                                    vtkVector2f* location);

  // Description:
  // Select all points in the specified rectangle.
  virtual bool SelectPoints(const vtkVector2f& min, const vtkVector2f& max);
//ETX

  // Description:
  // Set the plot color
  virtual void SetColor(unsigned char r, unsigned char g, unsigned char b,
                        unsigned char a);
  virtual void SetColor(double r,  double g, double b);
  virtual void GetColor(double rgb[3]);
  void GetColor(unsigned char rgb[3]);

  // Description:
  // Set the width of the line.
  virtual void SetWidth(float width);

  // Description:
  // Get the width of the line.
  virtual float GetWidth();

  // Description:
  // Get a pointer to the vtkPen object that controls the was this plot draws
  // lines.
  vtkGetObjectMacro(Pen, vtkPen);

  // Description:
  // Get a pointer to the vtkBrush object that controls the was this plot fills
  // shapes.
  vtkGetObjectMacro(Brush, vtkBrush);

  // Description:
  // Set the label of this plot.
  virtual void SetLabel(const vtkStdString &label);

  // Description:
  // Get the label of this plot.
  virtual vtkStdString GetLabel();

  // Description:
  // Set the plot labels, these are used for stacked chart variants, with the
  // index referring to the stacking index.
  virtual void SetLabels(vtkStringArray *labels);

  // Description:
  // Get the plot labels. If this array has a length greater than 1 the index
  // refers to the stacked objects in the plot. See vtkPlotBar for example.
  virtual vtkStringArray *GetLabels();

  // Description:
  // Get the number of labels associated with this plot.
  virtual int GetNumberOfLabels();

  // Description:
  // Get the label at the specified index.
  vtkStdString GetLabel(vtkIdType index);

  // Description:
  // Set indexed labels for the plot. If set, this array can be used to provide
  // custom labels for each point in a plot. This array should be the same
  // length as the points array. Default is null (no indexed labels).
  void SetIndexedLabels(vtkStringArray *labels);

  // Description:
  // Get the indexed labels array.
  virtual vtkStringArray *GetIndexedLabels();

  // Description:
  // Get the data object that the plot will draw.
  vtkGetObjectMacro(Data, vtkContextMapper2D);

  // Description:
  // Use the Y array index for the X value. If true any X column setting will be
  // ignored, and the X values will simply be the index of the Y column.
  vtkGetMacro(UseIndexForXSeries, bool);

  // Description:
  // Use the Y array index for the X value. If true any X column setting will be
  // ignored, and the X values will simply be the index of the Y column.
  vtkSetMacro(UseIndexForXSeries, bool);

  // Description:
  // This is a convenience function to set the input table and the x, y column
  // for the plot.
  virtual void SetInput(vtkTable *table);
  virtual void SetInput(vtkTable *table, const vtkStdString &xColumn,
                        const vtkStdString &yColumn);
  void SetInput(vtkTable *table, vtkIdType xColumn, vtkIdType yColumn);

  // Description:
  // Get the input table used by the plot.
  virtual vtkTable* GetInput();

  // Description:
  // Convenience function to set the input arrays. For most plots index 0
  // is the x axis, and index 1 is the y axis. The name is the name of the
  // column in the vtkTable.
  virtual void SetInputArray(int index, const vtkStdString &name);

  virtual void SetSelection(vtkIdTypeArray *id);
  vtkGetObjectMacro(Selection, vtkIdTypeArray);

  // Description:
  // Get/set the X axis associated with this plot.
  vtkGetObjectMacro(XAxis, vtkAxis);
  virtual void SetXAxis(vtkAxis* axis);

  // Description:
  // Get/set the Y axis associated with this plot.
  vtkGetObjectMacro(YAxis, vtkAxis);
  virtual void SetYAxis(vtkAxis* axis);

  // Description:
  // Get the bounds for this plot as (Xmin, Xmax, Ymin, Ymax).
  virtual void GetBounds(double bounds[4])
  { bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0.0; }

//BTX
  // Description:
  // A General setter/getter that should be overridden. It can silently drop
  // options, case is important
  virtual void SetProperty(const vtkStdString &property, const vtkVariant &var);
  virtual vtkVariant GetProperty(const vtkStdString &property);
//ETX

//BTX
protected:
  vtkPlot();
  ~vtkPlot();

  // Description:
  // Get the properly formatted number for the supplied position and axis.
  vtkStdString GetNumber(double position, vtkAxis *axis);

  // Description:
  // This object stores the vtkPen that controls how the plot is drawn.
  vtkPen* Pen;

  // Description:
  // This object stores the vtkBrush that controls how the plot is drawn.
  vtkBrush* Brush;

  // Description:
  // Plot labels, used by legend.
  vtkSmartPointer<vtkStringArray> Labels;

  // Description:
  // Holds Labels when they're auto-created
  vtkSmartPointer<vtkStringArray> AutoLabels;

  // Description:
  // Holds Labels when they're auto-created
  vtkSmartPointer<vtkStringArray> IndexedLabels;

  // Description:
  // Use the Y array index for the X value. If true any X column setting will be
  // ignored, and the X values will simply be the index of the Y column.
  bool UseIndexForXSeries;

  // Description:
  // This data member contains the data that will be plotted, it inherits
  // from vtkAlgorithm.
  vtkContextMapper2D *Data;

  // Description:
  // Selected indices for the table the plot is rendering
  vtkIdTypeArray *Selection;

  // Description:
  // The X axis associated with this plot.
  vtkAxis* XAxis;

  // Description:
  // The X axis associated with this plot.
  vtkAxis* YAxis;

  // Description:
  // A printf-style string to build custom tooltip labels from.
  // See the accessor/mutator functions for full documentation.
  vtkStdString TooltipLabelFormat;

  // Description:
  // The default printf-style string to build custom tooltip labels from.
  // See the accessor/mutator functions for full documentation.
  vtkStdString TooltipDefaultLabelFormat;

private:
  vtkPlot(const vtkPlot &); // Not implemented.
  void operator=(const vtkPlot &); // Not implemented.

//ETX
};

#endif //__vtkPlot_h
