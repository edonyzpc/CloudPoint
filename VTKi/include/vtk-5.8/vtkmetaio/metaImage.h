/*============================================================================
  MetaIO
  Copyright 2000-2010 Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "metaTypes.h"

#ifndef ITKMetaIO_METAIMAGE_H
#define ITKMetaIO_METAIMAGE_H

#include "metaUtils.h"
#include "metaObject.h"

#include "metaImageTypes.h"
#include "metaImageUtils.h"

/*!    MetaImage (.h and .cpp)
 *
 * Description:
 *    Reads and Writes MetaImageFiles.
 *    MetaImageFiles can be in one of two possible formats:
 *       a combined header/data format, typically designated .mha files
 *       or as separate header and data files, typically designated
 *       .mhd and .mda files
 *
 * Features:
 *    Header information is in ascii format - for easy creation, editing,
 *    and review. If separate files are used, a specified number of
 *    header-bytes in the datafile can be skipped
 *       - in this manner, different file formats (e.g., bmp, img,
 *          and /usr/Image) can be converted to metaImageFile format by
 *          merely specifying a separate text header (.mhd) file and in that
 *          file specifying how many data-header-bytes should be skipped.
 *          Thereby the data files can serve a dual role (as bitmap files
 *          and as metaImage data files) 
 *    Supports all pixel formats
 *    Handles byte ordering (MSB/LSB)
 *    Provides the ability to handle associated medical image
 *          information (element size, element spacing, etc).
 *    Has required and optional header data (provides rapid formation
 *          or extensive documentation).
 *    REQUIRED: NDims, DimSize, ByteOrderMSB, ElementDataType, DataFileName
 *
 * \author Stephen R. Aylward
 * 
 * \date August 29, 1999
 * 
 * Depends on:
 *    MetaUtils.h
 *    MetaFileLib.h
 */

#if (METAIO_USE_NAMESPACE)
namespace METAIO_NAMESPACE {
#endif

class METAIO_EXPORT MetaImage : public MetaObject
  {
  public:

    ////
    //
    // Constructors & Destructor
    //
    ////
    MetaImage(void);

    MetaImage(const char *_headerName);   

    MetaImage(MetaImage *_im);    // share memory

    MetaImage(int _nDims, 
              const int * _dimSize,
              const float *_elementSpacing,
              MET_ValueEnumType _elementType,
              int _elementNumberOfChannels=1,
              void *_elementData=NULL);

    MetaImage(int _x, int _y, 
              float _elementSpacingX, 
              float _elementSpacingY,
              MET_ValueEnumType _elementType, 
              int _elementNumberOfChannels=1,
              void *_elementData=NULL);

    MetaImage(int _x, int _y, int _z, 
              float _elementSpacingX,
              float _elementSpacingY,
              float _elementSpacingZ, 
              MET_ValueEnumType _elementType,
              int _elementNumberOfChannels=1,
              void *_elementData=NULL);

    ~MetaImage(void);

    virtual void PrintInfo(void) const;

    virtual void CopyInfo(const MetaObject * _object);

    virtual void Clear(void);

    virtual bool InitializeEssential(int _nDims, 
                                     const int * _dimSize,
                                     const float * _elementSpacing,
                                     MET_ValueEnumType _elementType,
                                     int _elementNumberOfChannels=1,
                                     void *_elementData=NULL,
                                     bool _allocElementMemory=true);

    //
    //
    //
    int   HeaderSize(void) const;
    void  HeaderSize(int _headerSize);

    MET_ImageModalityEnumType  Modality(void) const;
    void                       Modality(MET_ImageModalityEnumType _modality);

    //    DimSize(...)
    //       REQUIRED Field
    //       Number of elements along each dimension
    const int *  DimSize(void) const;
    int          DimSize(int _i) const;      
    //void  DimSize(const int * _dimSize);
    //void  DimSize(int _i, int _value);

    //    Quantity()
    //       Not a field in file
    //       Total number of elements in image (Prod(dimSize[i]))
    METAIO_STL::streamoff  Quantity(void) const;

    //    SubQuantity(...)
    //       Not a field in file
    //       Number of elements in image spanning sub-dimensions
    //       E.g., elements per line, 2D sub-image, 3D sub-volume,
    const METAIO_STL::streamoff * SubQuantity(void) const;      
    METAIO_STL::streamoff SubQuantity(int _i) const;  

    //    SequenceID(...)
    //       Optional Field
    //       DICOM designation of this image relative to other images
    //         acquired at the same time
    const float * SequenceID(void) const;
    float         SequenceID(int _i) const;
    void          SequenceID(const float * _sequenceID);
    void          SequenceID(int _i, float _value);

    //    ElemSize(...)
    //       Optional Field
    //       Physical size (in MM) of each element in the image
    //       (0 = xSize, 1 = ySize, 2 = zSize)
    bool           ElementSizeValid(void) const;
    void           ElementSizeValid(bool _elementSizeValid);
    const float *  ElementSize(void) const;
    float          ElementSize(int i) const;
    void           ElementSize(const float * _pointSize);
    void           ElementSize(int _i, float _value);

    MET_ValueEnumType ElementType(void) const;
    void              ElementType(MET_ValueEnumType _elementType);

    int   ElementNumberOfChannels(void) const;
    void  ElementNumberOfChannels(int _elementNumberOfChannels);

    //    ElemMakeByteOrderMSB(), ElemMakeByteOrderLSB(),
    //    ElemByteOrderSwap(), ElemByteOrderFix()
    //       The following functions are available only after
    //       ReadImageData() or if _read_and_close=TRUE when read
    //
    // if streaming is used, then the size of buffer in total number
    // of elements, should be passed as an argument, otherwise the
    // internal value Quantity() will be used
    void  ElementByteOrderSwap( METAIO_STL::streamoff _quantity = 0);
    bool  ElementByteOrderFix( METAIO_STL::streamoff _quantity = 0);

    //    Min(...) Max(...)
    //       The default max returned is the largest allowed by
    //         ElemNBytes (12 bit uint16_t will give 4096 max).
    //       This may not represent the true max.   Use _reCalc=true
    //         to force a calcuation of the actual max element value.
    bool   ElementMinMaxValid(void) const;
    void   ElementMinMaxValid(bool _elementMinMaxValid);
    void   ElementMinMaxRecalc(void);
    double ElementMin(void) const;    
    void   ElementMin(double _elementMin);
    double ElementMax(void) const;
    void   ElementMax(double _elementMax);

    //
    //
    //
    double ElementToIntensityFunctionSlope(void) const;
    void   ElementToIntensityFunctionSlope(double _slope);
    double ElementToIntensityFunctionOffset(void) const;
    void   ElementToIntensityFunctionOffset(double _offset);

    //
    //
    //
    bool   AutoFreeElementData(void) const;
    void   AutoFreeElementData(bool _freeData);


    //
    //
    //
    const char * ElementDataFileName(void) const;
    void         ElementDataFileName(const char * _dataFileName);

    //
    //
    //
    void * ElementData(void);
    double ElementData(METAIO_STL::streamoff _i) const;
    bool   ElementData(METAIO_STL::streamoff _i, double _v);
    void   ElementData(void * _data, bool _autoFreeElementData=false);

    //    ConverTo(...)
    //       Converts to a new data type
    //       Rescales using Min and Max (see above)
    bool  ConvertElementDataTo(MET_ValueEnumType _elementType=MET_USHORT,
                               double _toMin=0, double _toMax=0);
    bool  ConvertElementDataToIntensityData( MET_ValueEnumType
                                             _intensityType=MET_SHORT);
    bool  ConvertIntensityDataToElementData( MET_ValueEnumType
                                             _elementType=MET_USHORT);

    //
    //
    //
    virtual bool CanRead(const char *_headerName=NULL) const;

    virtual bool Read(const char *_headerName=NULL,
                      bool _readElements=true,
                      void * _buffer=NULL);

    virtual bool ReadROI(int * _indexMin, int * _indexMax,
                         const char *_headerName=NULL,
                         bool _readElements=true,
                         void * _buffer=NULL,
                         unsigned int subSamplingFactor=1
                         );


    virtual bool CanReadStream(METAIO_STREAM::ifstream * _stream) const;

    virtual bool ReadStream(int _nDims,
                            METAIO_STREAM::ifstream * _stream, 
                            bool _readElements=true,
                            void * _buffer=NULL);
 
    virtual bool ReadROIStream(int * _indexMin, int * _indexMax,
                               int _nDims,
                               METAIO_STREAM::ifstream * _stream, 
                               bool _readElements=true,
                               void * _buffer=NULL,
                               unsigned int subSamplingFactor=1);

    virtual bool Write(const char *_headName=NULL,
                       const char *_dataName=NULL,
                       bool _writeElements=true,
                       const void * _constElementData=NULL,
                       bool _append=false);

    virtual bool WriteROI(int * _indexMin, int * _indexMax,
                          const char *_headName=NULL,
                          const char *_dataName=NULL,
                          bool _writeElements=true,
                          const void * _constElementData=NULL,
                          bool _append=false
                          );

    virtual bool WriteStream(METAIO_STREAM::ofstream * _stream,
                             bool _writeElements=true,
                             const void * _constElementData=NULL);
    

    virtual bool Append(const char *_headName=NULL);


    typedef METAIO_STL::pair<long,long> CompressionOffsetType;

  ////
  //
  // PROTECTED
  //
  ////
  protected:

    MET_ImageModalityEnumType m_Modality;

                       
    MET_CompressionTableType*  m_CompressionTable;

    int                    m_DimSize[10];
    METAIO_STL::streamoff m_SubQuantity[10];
    METAIO_STL::streamoff m_Quantity;

    int                m_HeaderSize;

    float              m_SequenceID[4];

    bool               m_ElementSizeValid;
    float              m_ElementSize[10];

    MET_ValueEnumType  m_ElementType;

    int                m_ElementNumberOfChannels;

    bool               m_ElementMinMaxValid;
    double             m_ElementMin;
    double             m_ElementMax;

    double             m_ElementToIntensityFunctionSlope;
    double             m_ElementToIntensityFunctionOffset;

    bool               m_AutoFreeElementData;

    void  *            m_ElementData;

    char               m_ElementDataFileName[255];


    void  M_Destroy(void);

    void  M_SetupReadFields(void);

    void  M_SetupWriteFields(void);

    bool  M_Read(void);

    // _dataQuantity is expressed in number of pixels. Internally it will be
    // scaled by the number of components and number of bytes per component.
    bool  M_ReadElements(METAIO_STREAM::ifstream * _fstream, 
                         void * _data,
                         METAIO_STL::streamoff _dataQuantity);

    // _totalDataQuantity and _dataQuantity are expressed in number of pixels.
    // Internally they will be scaled by the number of components and number of
    // bytes per component.
    bool  M_ReadElementsROI(METAIO_STREAM::ifstream * _fstream, 
                            void * _data,
                            METAIO_STL::streamoff _dataQuantity,
                            int * _indexMin,
                            int* _indexMax,
                            unsigned int subSamplingFactor=1,
                            METAIO_STL::streamoff _totalDataQuantity=0);

    bool M_ReadElementData(METAIO_STREAM::ifstream * _fstream, 
                           void * _data,
                           METAIO_STL::streamoff _dataQuantity);

    bool  M_WriteElements(METAIO_STREAM::ofstream * _fstream,
                          const void * _data,
                          METAIO_STL::streamoff _dataQuantity);

    bool  M_WriteElementsROI(METAIO_STREAM::ofstream * _fstream,
                             const void * _data,
                             METAIO_STL::streampos _dataPos,
                             int * _indexMin,
                             int* _indexMax);

    bool  M_WriteElementData(METAIO_STREAM::ofstream * _fstream,
                             const void * _data,
                             METAIO_STL::streamoff _dataQuantity);

    bool M_FileExists(const char* filename) const;

    bool FileIsFullPath(const char* in_name) const;

    METAIO_STL::string M_GetTagValue(const METAIO_STL::string & buffer,
                                     const char* tag) const;

  };

#if (METAIO_USE_NAMESPACE)
};
#endif


#endif
