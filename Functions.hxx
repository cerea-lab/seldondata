// Copyright (C) 2003-2004 Vivien Mallet
//
// This file is part of SeldonData library.
// SeldonData library is a tool for data processing.
// 
// SeldonData is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// SeldonData is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (file "license") for more details.
//
// For more information, please see the SeldonData home page:
//     http://membres.lycos.fr/vmallet/seldondata/

#ifndef FILE_SELDONDATA_FUNCTIONS_HXX

namespace SeldonData
{
  
  template<int N, class TIn, class TGIn,
	   class TOut, class TGOut>
  void LinearInterpolationRegular(Data<TIn, N, TGIn>& dataIn,
				  Data<TOut, N, TGOut>& dataOut);

  template<int N, class TIn, class TGIn,
	   class TOut, class TGOut>
  void LinearInterpolationOneGeneral(Data<TIn, N, TGIn>& dataIn,
				     Data<TOut, N, TGOut>& dataOut,
				     int dim);
  
}  // namespace SeldonData.

#define FILE_SELDONDATA_FUNCTIONS_HXX
#endif
