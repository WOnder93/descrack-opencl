#ifndef DES_SBOXES_MKWAN_H
#define DES_SBOXES_MKWAN_H

/* DES s-boxes from Matthew Kwan */

#define s0(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54, x55, x56; \
    des_vector_t x57, x58, x59, x60, x61, x62, x63; \
\
    x1 = v_not(a4); \
    x2 = v_not(a1); \
    x3 = v_xor(a4, a3); \
    x4 = v_xor(x3, x2); \
    x5 = v_or(a3, x2); \
    x6 = v_and(x5, x1); \
    x7 = v_or(a6, x6); \
    x8 = v_xor(x4, x7); \
    x9 = v_or(x1, x2); \
    x10 = v_and(a6, x9); \
    x11 = v_xor(x7, x10); \
    x12 = v_or(a2, x11); \
    x13 = v_xor(x8, x12); \
    x14 = v_xor(x9, x13); \
    x15 = v_or(a6, x14); \
    x16 = v_xor(x1, x15); \
    x17 = v_not(x14); \
    x18 = v_and(x17, x3); \
    x19 = v_or(a2, x18); \
    x20 = v_xor(x16, x19); \
    x21 = v_or(a5, x20); \
    x22 = v_xor(x13, x21); \
    out4 = v_xor(l4, x22); \
    x23 = v_or(a3, x4); \
    x24 = v_not(x23); \
    x25 = v_or(a6, x24); \
    x26 = v_xor(x6, x25); \
    x27 = v_and(x1, x8); \
    x28 = v_or(a2, x27); \
    x29 = v_xor(x26, x28); \
    x30 = v_or(x1, x8); \
    x31 = v_xor(x30, x6); \
    x32 = v_and(x5, x14); \
    x33 = v_xor(x32, x8); \
    x34 = v_and(a2, x33); \
    x35 = v_xor(x31, x34); \
    x36 = v_or(a5, x35); \
    x37 = v_xor(x29, x36); \
    out1 = v_xor(l1, x37); \
    x38 = v_and(a3, x10); \
    x39 = v_or(x38, x4); \
    x40 = v_and(a3, x33); \
    x41 = v_xor(x40, x25); \
    x42 = v_or(a2, x41); \
    x43 = v_xor(x39, x42); \
    x44 = v_or(a3, x26); \
    x45 = v_xor(x44, x14); \
    x46 = v_or(a1, x8); \
    x47 = v_xor(x46, x20); \
    x48 = v_or(a2, x47); \
    x49 = v_xor(x45, x48); \
    x50 = v_and(a5, x49); \
    x51 = v_xor(x43, x50); \
    out2 = v_xor(l2, x51); \
    x52 = v_xor(x8, x40); \
    x53 = v_xor(a3, x11); \
    x54 = v_and(x53, x5); \
    x55 = v_or(a2, x54); \
    x56 = v_xor(x52, x55); \
    x57 = v_or(a6, x4); \
    x58 = v_xor(x57, x38); \
    x59 = v_and(x13, x56); \
    x60 = v_and(a2, x59); \
    x61 = v_xor(x58, x60); \
    x62 = v_and(a5, x61); \
    x63 = v_xor(x56, x62); \
    out3 = v_xor(l3, x63); \
} while (0)

#define s1(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54, x55, x56; \
\
    x1 = v_not(a5); \
    x2 = v_not(a1); \
    x3 = v_xor(a5, a6); \
    x4 = v_xor(x3, x2); \
    x5 = v_xor(x4, a2); \
    x6 = v_or(a6, x1); \
    x7 = v_or(x6, x2); \
    x8 = v_and(a2, x7); \
    x9 = v_xor(a6, x8); \
    x10 = v_and(a3, x9); \
    x11 = v_xor(x5, x10); \
    x12 = v_and(a2, x9); \
    x13 = v_xor(a5, x6); \
    x14 = v_or(a3, x13); \
    x15 = v_xor(x12, x14); \
    x16 = v_and(a4, x15); \
    x17 = v_xor(x11, x16); \
    out2 = v_xor(l2, x17); \
    x18 = v_or(a5, a1); \
    x19 = v_or(a6, x18); \
    x20 = v_xor(x13, x19); \
    x21 = v_xor(x20, a2); \
    x22 = v_or(a6, x4); \
    x23 = v_and(x22, x17); \
    x24 = v_or(a3, x23); \
    x25 = v_xor(x21, x24); \
    x26 = v_or(a6, x2); \
    x27 = v_and(a5, x2); \
    x28 = v_or(a2, x27); \
    x29 = v_xor(x26, x28); \
    x30 = v_xor(x3, x27); \
    x31 = v_xor(x2, x19); \
    x32 = v_and(a2, x31); \
    x33 = v_xor(x30, x32); \
    x34 = v_and(a3, x33); \
    x35 = v_xor(x29, x34); \
    x36 = v_or(a4, x35); \
    x37 = v_xor(x25, x36); \
    out3 = v_xor(l3, x37); \
    x38 = v_and(x21, x32); \
    x39 = v_xor(x38, x5); \
    x40 = v_or(a1, x15); \
    x41 = v_xor(x40, x13); \
    x42 = v_or(a3, x41); \
    x43 = v_xor(x39, x42); \
    x44 = v_or(x28, x41); \
    x45 = v_and(a4, x44); \
    x46 = v_xor(x43, x45); \
    out1 = v_xor(l1, x46); \
    x47 = v_and(x19, x21); \
    x48 = v_xor(x47, x26); \
    x49 = v_and(a2, x33); \
    x50 = v_xor(x49, x21); \
    x51 = v_and(a3, x50); \
    x52 = v_xor(x48, x51); \
    x53 = v_and(x18, x28); \
    x54 = v_and(x53, x50); \
    x55 = v_or(a4, x54); \
    x56 = v_xor(x52, x55); \
    out4 = v_xor(l4, x56); \
} while (0)

#define s2(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54, x55, x56; \
    des_vector_t x57; \
\
    x1 = v_not(a5); \
    x2 = v_not(a6); \
    x3 = v_and(a5, a3); \
    x4 = v_xor(x3, a6); \
    x5 = v_and(a4, x1); \
    x6 = v_xor(x4, x5); \
    x7 = v_xor(x6, a2); \
    x8 = v_and(a3, x1); \
    x9 = v_xor(a5, x2); \
    x10 = v_or(a4, x9); \
    x11 = v_xor(x8, x10); \
    x12 = v_and(x7, x11); \
    x13 = v_xor(a5, x11); \
    x14 = v_or(x13, x7); \
    x15 = v_and(a4, x14); \
    x16 = v_xor(x12, x15); \
    x17 = v_and(a2, x16); \
    x18 = v_xor(x11, x17); \
    x19 = v_and(a1, x18); \
    x20 = v_xor(x7, x19); \
    out4 = v_xor(l4, x20); \
    x21 = v_xor(a3, a4); \
    x22 = v_xor(x21, x9); \
    x23 = v_or(x2, x4); \
    x24 = v_xor(x23, x8); \
    x25 = v_or(a2, x24); \
    x26 = v_xor(x22, x25); \
    x27 = v_xor(a6, x23); \
    x28 = v_or(x27, a4); \
    x29 = v_xor(a3, x15); \
    x30 = v_or(x29, x5); \
    x31 = v_or(a2, x30); \
    x32 = v_xor(x28, x31); \
    x33 = v_or(a1, x32); \
    x34 = v_xor(x26, x33); \
    out1 = v_xor(l1, x34); \
    x35 = v_xor(a3, x9); \
    x36 = v_or(x35, x5); \
    x37 = v_or(x4, x29); \
    x38 = v_xor(x37, a4); \
    x39 = v_or(a2, x38); \
    x40 = v_xor(x36, x39); \
    x41 = v_and(a6, x11); \
    x42 = v_or(x41, x6); \
    x43 = v_xor(x34, x38); \
    x44 = v_xor(x43, x41); \
    x45 = v_and(a2, x44); \
    x46 = v_xor(x42, x45); \
    x47 = v_or(a1, x46); \
    x48 = v_xor(x40, x47); \
    out3 = v_xor(l3, x48); \
    x49 = v_or(x2, x38); \
    x50 = v_xor(x49, x13); \
    x51 = v_xor(x27, x28); \
    x52 = v_or(a2, x51); \
    x53 = v_xor(x50, x52); \
    x54 = v_and(x12, x23); \
    x55 = v_and(x54, x52); \
    x56 = v_or(a1, x55); \
    x57 = v_xor(x53, x56); \
    out2 = v_xor(l2, x57); \
} while (0)

#define s3(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42; \
\
    x1 = v_not(a1); \
    x2 = v_not(a3); \
    x3 = v_or(a1, a3); \
    x4 = v_and(a5, x3); \
    x5 = v_xor(x1, x4); \
    x6 = v_or(a2, a3); \
    x7 = v_xor(x5, x6); \
    x8 = v_and(a1, a5); \
    x9 = v_xor(x8, x3); \
    x10 = v_and(a2, x9); \
    x11 = v_xor(a5, x10); \
    x12 = v_and(a4, x11); \
    x13 = v_xor(x7, x12); \
    x14 = v_xor(x2, x4); \
    x15 = v_and(a2, x14); \
    x16 = v_xor(x9, x15); \
    x17 = v_and(x5, x14); \
    x18 = v_xor(a5, x2); \
    x19 = v_or(a2, x18); \
    x20 = v_xor(x17, x19); \
    x21 = v_or(a4, x20); \
    x22 = v_xor(x16, x21); \
    x23 = v_and(a6, x22); \
    x24 = v_xor(x13, x23); \
    out2 = v_xor(l2, x24); \
    x25 = v_not(x13); \
    x26 = v_or(a6, x22); \
    x27 = v_xor(x25, x26); \
    out1 = v_xor(l1, x27); \
    x28 = v_and(a2, x11); \
    x29 = v_xor(x28, x17); \
    x30 = v_xor(a3, x10); \
    x31 = v_xor(x30, x19); \
    x32 = v_and(a4, x31); \
    x33 = v_xor(x29, x32); \
    x34 = v_xor(x25, x33); \
    x35 = v_and(a2, x34); \
    x36 = v_xor(x24, x35); \
    x37 = v_or(a4, x34); \
    x38 = v_xor(x36, x37); \
    x39 = v_and(a6, x38); \
    x40 = v_xor(x33, x39); \
    out4 = v_xor(l4, x40); \
    x41 = v_xor(x26, x38); \
    x42 = v_xor(x41, x40); \
    out3 = v_xor(l3, x42); \
} while (0)

#define s4(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54, x55, x56; \
    des_vector_t x57, x58, x59, x60, x61, x62; \
\
    x1 = v_not(a6); \
    x2 = v_not(a3); \
    x3 = v_or(x1, x2); \
    x4 = v_xor(x3, a4); \
    x5 = v_and(a1, x3); \
    x6 = v_xor(x4, x5); \
    x7 = v_or(a6, a4); \
    x8 = v_xor(x7, a3); \
    x9 = v_or(a3, x7); \
    x10 = v_or(a1, x9); \
    x11 = v_xor(x8, x10); \
    x12 = v_and(a5, x11); \
    x13 = v_xor(x6, x12); \
    x14 = v_not(x4); \
    x15 = v_and(x14, a6); \
    x16 = v_or(a1, x15); \
    x17 = v_xor(x8, x16); \
    x18 = v_or(a5, x17); \
    x19 = v_xor(x10, x18); \
    x20 = v_or(a2, x19); \
    x21 = v_xor(x13, x20); \
    out3 = v_xor(l3, x21); \
    x22 = v_or(x2, x15); \
    x23 = v_xor(x22, a6); \
    x24 = v_xor(a4, x22); \
    x25 = v_and(a1, x24); \
    x26 = v_xor(x23, x25); \
    x27 = v_xor(a1, x11); \
    x28 = v_and(x27, x22); \
    x29 = v_or(a5, x28); \
    x30 = v_xor(x26, x29); \
    x31 = v_or(a4, x27); \
    x32 = v_not(x31); \
    x33 = v_or(a2, x32); \
    x34 = v_xor(x30, x33); \
    out2 = v_xor(l2, x34); \
    x35 = v_xor(x2, x15); \
    x36 = v_and(a1, x35); \
    x37 = v_xor(x14, x36); \
    x38 = v_xor(x5, x7); \
    x39 = v_and(x38, x34); \
    x40 = v_or(a5, x39); \
    x41 = v_xor(x37, x40); \
    x42 = v_xor(x2, x5); \
    x43 = v_and(x42, x16); \
    x44 = v_and(x4, x27); \
    x45 = v_and(a5, x44); \
    x46 = v_xor(x43, x45); \
    x47 = v_or(a2, x46); \
    x48 = v_xor(x41, x47); \
    out1 = v_xor(l1, x48); \
    x49 = v_and(x24, x48); \
    x50 = v_xor(x49, x5); \
    x51 = v_xor(x11, x30); \
    x52 = v_or(x51, x50); \
    x53 = v_and(a5, x52); \
    x54 = v_xor(x50, x53); \
    x55 = v_xor(x14, x19); \
    x56 = v_xor(x55, x34); \
    x57 = v_xor(x4, x16); \
    x58 = v_and(x57, x30); \
    x59 = v_and(a5, x58); \
    x60 = v_xor(x56, x59); \
    x61 = v_or(a2, x60); \
    x62 = v_xor(x54, x61); \
    out4 = v_xor(l4, x62); \
} while (0)

#define s5(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54, x55, x56; \
    des_vector_t x57; \
\
    x1 = v_not(a2); \
    x2 = v_not(a5); \
    x3 = v_xor(a2, a6); \
    x4 = v_xor(x3, x2); \
    x5 = v_xor(x4, a1); \
    x6 = v_and(a5, a6); \
    x7 = v_or(x6, x1); \
    x8 = v_and(a5, x5); \
    x9 = v_and(a1, x8); \
    x10 = v_xor(x7, x9); \
    x11 = v_and(a4, x10); \
    x12 = v_xor(x5, x11); \
    x13 = v_xor(a6, x10); \
    x14 = v_and(x13, a1); \
    x15 = v_and(a2, a6); \
    x16 = v_xor(x15, a5); \
    x17 = v_and(a1, x16); \
    x18 = v_xor(x2, x17); \
    x19 = v_or(a4, x18); \
    x20 = v_xor(x14, x19); \
    x21 = v_and(a3, x20); \
    x22 = v_xor(x12, x21); \
    out2 = v_xor(l2, x22); \
    x23 = v_xor(a6, x18); \
    x24 = v_and(a1, x23); \
    x25 = v_xor(a5, x24); \
    x26 = v_xor(a2, x17); \
    x27 = v_or(x26, x6); \
    x28 = v_and(a4, x27); \
    x29 = v_xor(x25, x28); \
    x30 = v_not(x26); \
    x31 = v_or(a6, x29); \
    x32 = v_not(x31); \
    x33 = v_and(a4, x32); \
    x34 = v_xor(x30, x33); \
    x35 = v_and(a3, x34); \
    x36 = v_xor(x29, x35); \
    out4 = v_xor(l4, x36); \
    x37 = v_xor(x6, x34); \
    x38 = v_and(a5, x23); \
    x39 = v_xor(x38, x5); \
    x40 = v_or(a4, x39); \
    x41 = v_xor(x37, x40); \
    x42 = v_or(x16, x24); \
    x43 = v_xor(x42, x1); \
    x44 = v_xor(x15, x24); \
    x45 = v_xor(x44, x31); \
    x46 = v_or(a4, x45); \
    x47 = v_xor(x43, x46); \
    x48 = v_or(a3, x47); \
    x49 = v_xor(x41, x48); \
    out1 = v_xor(l1, x49); \
    x50 = v_or(x5, x38); \
    x51 = v_xor(x50, x6); \
    x52 = v_and(x8, x31); \
    x53 = v_or(a4, x52); \
    x54 = v_xor(x51, x53); \
    x55 = v_and(x30, x43); \
    x56 = v_or(a3, x55); \
    x57 = v_xor(x54, x56); \
    out3 = v_xor(l3, x57); \
} while (0)

#define s6(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54, x55, x56; \
    des_vector_t x57; \
\
    x1 = v_not(a2); \
    x2 = v_not(a5); \
    x3 = v_and(a2, a4); \
    x4 = v_xor(x3, a5); \
    x5 = v_xor(x4, a3); \
    x6 = v_and(a4, x4); \
    x7 = v_xor(x6, a2); \
    x8 = v_and(a3, x7); \
    x9 = v_xor(a1, x8); \
    x10 = v_or(a6, x9); \
    x11 = v_xor(x5, x10); \
    x12 = v_and(a4, x2); \
    x13 = v_or(x12, a2); \
    x14 = v_or(a2, x2); \
    x15 = v_and(a3, x14); \
    x16 = v_xor(x13, x15); \
    x17 = v_xor(x6, x11); \
    x18 = v_or(a6, x17); \
    x19 = v_xor(x16, x18); \
    x20 = v_and(a1, x19); \
    x21 = v_xor(x11, x20); \
    out1 = v_xor(l1, x21); \
    x22 = v_or(a2, x21); \
    x23 = v_xor(x22, x6); \
    x24 = v_xor(x23, x15); \
    x25 = v_xor(x5, x6); \
    x26 = v_or(x25, x12); \
    x27 = v_or(a6, x26); \
    x28 = v_xor(x24, x27); \
    x29 = v_and(x1, x19); \
    x30 = v_and(x23, x26); \
    x31 = v_and(a6, x30); \
    x32 = v_xor(x29, x31); \
    x33 = v_or(a1, x32); \
    x34 = v_xor(x28, x33); \
    out4 = v_xor(l4, x34); \
    x35 = v_and(a4, x16); \
    x36 = v_or(x35, x1); \
    x37 = v_and(a6, x36); \
    x38 = v_xor(x11, x37); \
    x39 = v_and(a4, x13); \
    x40 = v_or(a3, x7); \
    x41 = v_xor(x39, x40); \
    x42 = v_or(x1, x24); \
    x43 = v_or(a6, x42); \
    x44 = v_xor(x41, x43); \
    x45 = v_or(a1, x44); \
    x46 = v_xor(x38, x45); \
    out2 = v_xor(l2, x46); \
    x47 = v_xor(x8, x44); \
    x48 = v_xor(x6, x15); \
    x49 = v_or(a6, x48); \
    x50 = v_xor(x47, x49); \
    x51 = v_xor(x19, x44); \
    x52 = v_xor(a4, x25); \
    x53 = v_and(x52, x46); \
    x54 = v_and(a6, x53); \
    x55 = v_xor(x51, x54); \
    x56 = v_or(a1, x55); \
    x57 = v_xor(x50, x56); \
    out3 = v_xor(l3, x57); \
} while (0)

#define s7(_a1, _a2, _a3, _a4, _a5, _a6, l1, l2, l3, l4, out1, out2, out3, out4) do { \
    des_vector_t a1 = _a1, a2 = _a2, a3 = _a3, a4 = _a4, a5 = _a5, a6 = _a6; \
    des_vector_t x1, x2, x3, x4, x5, x6, x7, x8; \
    des_vector_t x9, x10, x11, x12, x13, x14, x15, x16; \
    des_vector_t x17, x18, x19, x20, x21, x22, x23, x24; \
    des_vector_t x25, x26, x27, x28, x29, x30, x31, x32; \
    des_vector_t x33, x34, x35, x36, x37, x38, x39, x40; \
    des_vector_t x41, x42, x43, x44, x45, x46, x47, x48; \
    des_vector_t x49, x50, x51, x52, x53, x54; \
\
    x1 = v_not(a1); \
    x2 = v_not(a4); \
    x3 = v_xor(a3, x1); \
    x4 = v_or(a3, x1); \
    x5 = v_xor(x4, x2); \
    x6 = v_or(a5, x5); \
    x7 = v_xor(x3, x6); \
    x8 = v_or(x1, x5); \
    x9 = v_xor(x2, x8); \
    x10 = v_and(a5, x9); \
    x11 = v_xor(x8, x10); \
    x12 = v_and(a2, x11); \
    x13 = v_xor(x7, x12); \
    x14 = v_xor(x6, x9); \
    x15 = v_and(x3, x9); \
    x16 = v_and(a5, x8); \
    x17 = v_xor(x15, x16); \
    x18 = v_or(a2, x17); \
    x19 = v_xor(x14, x18); \
    x20 = v_or(a6, x19); \
    x21 = v_xor(x13, x20); \
    out1 = v_xor(l1, x21); \
    x22 = v_or(a5, x3); \
    x23 = v_and(x22, x2); \
    x24 = v_not(a3); \
    x25 = v_and(x24, x8); \
    x26 = v_and(a5, x4); \
    x27 = v_xor(x25, x26); \
    x28 = v_or(a2, x27); \
    x29 = v_xor(x23, x28); \
    x30 = v_and(a6, x29); \
    x31 = v_xor(x13, x30); \
    out4 = v_xor(l4, x31); \
    x32 = v_xor(x5, x6); \
    x33 = v_xor(x32, x22); \
    x34 = v_or(a4, x13); \
    x35 = v_and(a2, x34); \
    x36 = v_xor(x33, x35); \
    x37 = v_and(a1, x33); \
    x38 = v_xor(x37, x8); \
    x39 = v_xor(a1, x23); \
    x40 = v_and(x39, x7); \
    x41 = v_and(a2, x40); \
    x42 = v_xor(x38, x41); \
    x43 = v_or(a6, x42); \
    x44 = v_xor(x36, x43); \
    out3 = v_xor(l3, x44); \
    x45 = v_xor(a1, x10); \
    x46 = v_xor(x45, x22); \
    x47 = v_not(x7); \
    x48 = v_and(x47, x8); \
    x49 = v_or(a2, x48); \
    x50 = v_xor(x46, x49); \
    x51 = v_xor(x19, x29); \
    x52 = v_or(x51, x38); \
    x53 = v_and(a6, x52); \
    x54 = v_xor(x50, x53); \
    out2 = v_xor(l2, x54); \
} while (0)

#endif // DES_SBOXES_MKWAN_H

