/*
	Copyright (c) 2015-2016 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

#include "wxchartscore.h"

wxChartArc::wxChartArc(const wxColor &fillColor)
	: fillColor(fillColor)
{
}

void wxChartArc::draw(wxGraphicsContext &gc)
{
	wxGraphicsPath path = gc.CreatePath();
	path.AddArc(75, 75, 30, startAngle, endAngle, true);
	path.AddArc(75, 75, 75, endAngle, startAngle, false);
	path.CloseSubpath();

	wxBrush brush(fillColor);
	gc.SetBrush(brush);
	gc.FillPath(path);

	wxPen pen(*wxWHITE, 2);
	gc.SetPen(pen);
	gc.StrokePath(path);
}

void wxChartRectangle::draw(wxGraphicsContext &gc)
{
}
