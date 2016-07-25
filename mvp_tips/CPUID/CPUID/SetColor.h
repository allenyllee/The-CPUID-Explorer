#define SETCOLOR(x) \
       { \
        c_##x.SetBkColor(colors.GetNextColor(p)); \
        x_##x.SetBkColor(c_##x.GetBkColor()); \
       }

#define SETCOLORc(x) \
                     c_##x.SetBkColor(colors.GetNextColor(p)); 

#define SETCOLORx(x) \
        x_##x.SetBkColor(colors.GetNextColor(p)); 
                     
#define SETCOLORI(x,n) \
                    { \
                    c_##x.SetBkColor(colors.GetColor(n)); \
                    x_##x.SetBkColor(c_##x.GetBkColor()); \
                    }

#define SETCOLORIc(x, n) \
                     c_##x.SetBkColor(colors.GetColor(n)); 

#define SETCOLORIx(x, n) \
                     x_##x.SetBkColor(colors.GetColor(n)); 

#define SETRESERVEDCOLOR(x) \
       { \
        c_##x.SetBkColor(RGB(145,145,145));  \
        x_##x.SetBkColor(c_##x.GetBkColor()); \
       }
#define SETRESERVEDCOLORc(x) \
        c_##x.SetBkColor(RGB(145,145,145)); 

#define SETRESERVEDCOLORx(x) \
        x_##x.SetBkColor(RGB(145,145,145)); 
