#pragma once
class ColorSet {
    public:
       ColorSet() {}
       ColorSet(BOOL init);
       ColorSet(const COLORREF * colors, INT_PTR len)
          { 
           Initialize(colors, len);
          }
       void Add(COLORREF c) { colortable.Add(c); }
       POSITION GetFirstColorPosition() { return (POSITION) 0; }
       COLORREF GetNextColor(POSITION & p) {
          COLORREF result = colortable[(INT_PTR&)p];
          ((INT_PTR&)p)++;
          if((INT_PTR&)p >= colortable.GetSize())
             p = (POSITION)0;
          return result;
       }
       COLORREF GetColor(INT_PTR n) {
          return colortable[n % colortable.GetSize()];
       }
    protected:
       static const COLORREF colors[];
       CArray<COLORREF, COLORREF>colortable;
       void Initialize(const COLORREF * colors, INT_PTR len)
          {
           for(INT_PTR i = 0; i < len; i++)
              Add(colors[i]);
          }          
};
