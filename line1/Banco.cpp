#include "pch.h"
#include "Banco.h"

Banco::Banco()
{
    dk = 0;
    diem = 0;
    thang = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < D; i++)
        for (j = 0; j < R; j++)
        {
        

            bc[i][j] = Hcn(XD + j * l, YD + i * l, XD + (j + 1) * l, YD + (i + 1) * l, -1);
            oc[i][j] = Tron();
        }
    octiep = Tron();
    giatritiep = 0;
}

void Banco::vehinh(CClientDC* pdc)
{
    CString strdiem, strstart, strstop;
    strdiem.Format(_T("Diem: %d"), diem);
    strstart.Format(_T("nhan phim cach de bat dau choi "));
    strstop.Format(_T("Game over"));

    for (int i = 0; i < D; i++) {
        for (int j = 0; j < R; j++)
        {
            bc[i][j].vehinh(pdc);
            oc[i][j].vehinh(pdc);
        }
    }
    octiep.vehinh(pdc);
    if (dk == 0 && thang == 0) {
        pdc->TextOutW(XD + l * 2, YD + D * l / 2, strstart);
    }
    if (thang == 1) {
        pdc->TextOutW(XD + l * 2, YD + D * l / 2, strstop);
    }
    pdc->TextOutW(XD, YD / 2, strdiem);
}

void Banco::batdau()
{
    if (dk == 1)
        return;
    dk = 1;
    diem = 0;
    taobuocditiep();
}

void Banco::bamchuot(CClientDC* pdc, CPoint p)
{
    if (dk == 0) {
        OutputDebugString(_T("Game is not started yet.\n"));
        return;
    }

    // Debugging information
    OutputDebugString(_T("Mouse click detected.\n"));

    // Tiếp tục xử lý sau khi xác nhận rằng sự kiện chuột đã được nhận
    int mangi[5]{};
    int mangj[5]{};
    int dabam = 0;
    int mi = 1;
    for (int i = 0; i < 5; i++) {
        mangi[i] = -1;
        mangj[i] = -1;
    }
    // Kiểm tra sự kiện chuột vào ô nào
    for (int i = 0; i < D; i++)
        for (int j = 0; j < R; j++) {
            if (bc[i][j].kttronghinh(p) == 1 && bc[i][j].trangthai == 0) {
                oc[i][j].thietlapgiatri(XD + j * l + 5, YD + i * l + 5, l - 10, giatritiep);
                bc[i][j].giatri = giatritiep;
                bc[i][j].trangthai = 1;
                dabam = 1;
                mangi[0] = i;
                mangj[0] = j;
            }
        }
    // Tiếp tục xử lý nếu có ô được nhấp vào
    if (dabam == 1) {
        // Thêm các xử lý sau khi có sự kiện
        vehinh(pdc);
        Sleep(50);
        kiemtratinhdiem(mangi, mangj);
        if (taobuocditiep() == 0) {
            thang = 1;
            dk = 0;
        }
    }
    vehinh(pdc);
}

int Banco::kiemtratinhdiem(int mangi[], int mangj[])
{
    for (int i = 0; i < 5; i++) {
        kiemtrathang(mangi[i], mangj[i]);
        kiemtrangang(mangi[i], mangj[i]);
        kiemtracheo1(mangi[i], mangj[i]);
        kiemtracheo2(mangi[i], mangj[i]);
    }
    return 0;
}

void Banco::kiemtrathang(int mi, int mj)
{
    int dem = 0;
    // len tren
    int i = mi - 1;
    int j = mj;
    while (i >= 0) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        i--;
    }
    // xuong
    i = mi + 1;
    while (i < D) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        i++;
    }
    if (dem >= 4) {
        diem = diem + dem * 2;
        // xoa o co
        i = mi - 1;
        while (i >= 0) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            i--;
        }
        i = mi + 1;
        while (i < D) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            i++;
        }
        bc[mi][mj].giatri = -1;
        bc[mi][mj].trangthai = 0;
        oc[mi][mj].thietlapgiatri(0, 0, 0, 0);
    }
}

void Banco::kiemtrangang(int mi, int mj)
{
    int dem = 0;
    // qua trai
    int i = mi;
    int j = mj - 1;
    while (j >= 0) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        j--;
    }
    // qua phai
    j = mj + 1;
    while (j < R) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        j++;
    }
    if (dem >= 4) {
        diem = diem + dem * 2;
        // xoa o co
        j = mj - 1;
        while (j >= 0) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            j--;
        }
        j = mj + 1;
        while (j < R) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            j++;
        }
        bc[mi][mj].giatri = -1;
        bc[mi][mj].trangthai = 0;
        oc[mi][mj].thietlapgiatri(0, 0, 0, 0);
    }
}


void Banco::kiemtracheo1(int mi, int mj)
{
    int dem = 0;
    // di len
    int i = mi - 1;
    int j = mj - 1;
    while (j >= 0 && i >= 0) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        j--;
        i--;
    }
    // xuong duoi
    i = mi + 1;
    j = mj + 1;
    while (j < R && i < D) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        j++;
        i++;
    }
    if (dem >= 4) {
        diem = diem + dem * 2;
        // xoa o co
        i = mi - 1;
        j = mj - 1;
        while (i >= 0 && j >= 0) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            j--;
            i--;
        }
        i = mi + 1;
        j = mj + 1;
        while (i < D && j < R) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            j++;
            i++;
        }
        bc[mi][mj].giatri = -1;
        bc[mi][mj].trangthai = 0;
        oc[mi][mj].thietlapgiatri(0, 0, 0, 0);
    }
}

void Banco::kiemtracheo2(int mi, int mj)
{
    int dem = 0;
    // di len
    int i = mi - 1;
    int j = mj + 1;
    while (j < R && i >= 0) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        j++;
        i--;
    }
    // xuong duoi
    i = mi + 1;
    j = mj - 1;
    while (j >= 0 && i < D) {
        if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            dem++;
        else
            break;
        j--;
        i++;
    }
    if (dem >= 4) {
        diem = diem + dem * 2;
        // xoa o co
        i = mi - 1;
        j = mj + 1;
        while (i >= 0 && j < R) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            j++;
            i--;
        }
        i = mi + 1;
        j = mj - 1;
        while (i < D && j >= 0) {
            if (bc[i][j].giatri == bc[mi][mj].giatri && bc[i][j].trangthai == 1)
            {
                bc[i][j].giatri = -1;
                bc[i][j].trangthai = 0;
                oc[i][j].thietlapgiatri(0, 0, 0, 0);
            }
            else
                break;
            j--;
            i++;
        }
        bc[mi][mj].giatri = -1;
        bc[mi][mj].trangthai = 0;
        oc[mi][mj].thietlapgiatri(0, 0, 0, 0);
    }
}

int Banco::taobuocditiep()
{
    int dem = 0;
    int i = -1;
    int j = -1;
    int t = 0;
    // tao danh sach cac i, j co the lay de tao vi tri tiep theo
    int mangi[R * D];
    int mangj[R * D];
    int n = 0;
    for (i = 0; i < D; i++) {
        for (j = 0; j < R; j++) {
            if (bc[i][j].giatri == -1) {
                mangi[n] = i;
                mangj[n] = j;
                n++;
            }
        }
    }
    while (dem < 4 && dem < n) {
        t = rand() % n; // Changed to 'n' to avoid exceeding bounds
        int randI = mangi[t];
        int randJ = mangj[t];
        int value = rand() % 5;
        bc[randI][randJ].giatri = value;
        oc[randI][randJ].thietlapgiatri(XD + randJ * l + l / 2 - 5, YD + randI * l + l / 2 - 5, 10, value);
        dem++;
    }
    t = rand() % 5;
    octiep.thietlapgiatri(XD + l * R / 2, YD / 2 - l / 2, l, t);
    giatritiep = t;
    return dem;
}
