#include "c_compat.h"

#if !defined(CONFIG_VECTOR) || CONFIG_VECTOR == CONFIG_VECTOR_UINT
#include "des_vector_uint.h"
#else
#error "Invalid vector configuration!"
#endif

#if DES_VECTOR_LEVEL + BITS_GLOBAL > 32
#error "BITS_GLOBAL must be at most 32 - DES_VECTOR_LEVEL!"
#endif

#if !defined(CONFIG_SBOXES) || CONFIG_SBOXES == CONFIG_SBOXES_OPENWALL
#include "des_sboxes_openwall.h"
#elif CONFIG_SBOXES == CONFIG_SBOXES_OPENWALL_BITSEL
#include "des_sboxes_openwall_bitsel.h"
#elif CONFIG_SBOXES == CONFIG_SBOXES_MKWAN
#include "des_sboxes_mkwan.h"
#else
#error "Invalid s-box configuration!"
#endif

#include "des_tables.h"

#define EXTRACT_CD(cd, cd_base, bit) ( \
    (bit) >= BITS_GLOBAL ? \
    cd_base[(bit) - BITS_GLOBAL] : \
    select(v_zero, v_ones, (cd) & ((uint)0x1u << (bit))) \
)

#define S_BOX(box, round, cd, cd_base, l0, r0, r) do { \
    s##box( \
    v_xor(r0[EP(box, 0)], EXTRACT_CD(cd, cd_base, KEY_SCHEDULE(round, box, 0))), \
    v_xor(r0[EP(box, 1)], EXTRACT_CD(cd, cd_base, KEY_SCHEDULE(round, box, 1))), \
    v_xor(r0[EP(box, 2)], EXTRACT_CD(cd, cd_base, KEY_SCHEDULE(round, box, 2))), \
    v_xor(r0[EP(box, 3)], EXTRACT_CD(cd, cd_base, KEY_SCHEDULE(round, box, 3))), \
    v_xor(r0[EP(box, 4)], EXTRACT_CD(cd, cd_base, KEY_SCHEDULE(round, box, 4))), \
    v_xor(r0[EP(box, 5)], EXTRACT_CD(cd, cd_base, KEY_SCHEDULE(round, box, 5))), \
    l0[PI(box, 0)], \
    l0[PI(box, 1)], \
    l0[PI(box, 2)], \
    l0[PI(box, 3)], \
    r[PI(box, 0)], \
    r[PI(box, 1)], \
    r[PI(box, 2)], \
    r[PI(box, 3)]); \
} while(0)

#define S_BOXES(round, cd, cd_base, l0, r0, r) do { \
    S_BOX(0, round, cd, cd_base, l0, r0, r); \
    S_BOX(1, round, cd, cd_base, l0, r0, r); \
    S_BOX(2, round, cd, cd_base, l0, r0, r); \
    S_BOX(3, round, cd, cd_base, l0, r0, r); \
    S_BOX(4, round, cd, cd_base, l0, r0, r); \
    S_BOX(5, round, cd, cd_base, l0, r0, r); \
    S_BOX(6, round, cd, cd_base, l0, r0, r); \
    S_BOX(7, round, cd, cd_base, l0, r0, r); \
} while(0)


__kernel
void des_kernel(
        __constant  des_vector *input,
        __constant  des_vector *output,
        __local     des_vector *tmp0,
        __local     des_vector *tmp1,
        __constant  uint *cd_base,
        __global    uint *result_buffer,
        uint bits_thread)
{
    size_t id = get_global_id(0);

    if (id == 0) {
        result_buffer[0] = 0;
    }

    __constant des_vector * const i0 = input;
    __constant des_vector * const i1 = input + 32;

    __constant des_vector * const o0 = output;
    __constant des_vector * const o1 = output + 32;

    uint count = (uint)1 << bits_thread;
    uint cd_l = (uint)id << bits_thread;
    uint cd_u = cd_l + count;
    __local des_vector *b0 = tmp0[get_local_id(0) * 32];
    __local des_vector *b1 = tmp1[get_local_id(0) * 32];
    for (uint cd = cd_l; cd < cd_u; cd++) {
        S_BOXES(0, cd, cd_base, i0, i1, b0);
        S_BOXES(1, cd, cd_base, i1, b0, b1);
        S_BOXES(2, cd, cd_base, b0, b1, b0);
        S_BOXES(3, cd, cd_base, b1, b0, b1);
        S_BOXES(4, cd, cd_base, b0, b1, b0);
        S_BOXES(5, cd, cd_base, b1, b0, b1);
        S_BOXES(6, cd, cd_base, b0, b1, b0);
        S_BOXES(7, cd, cd_base, b1, b0, b1);
        S_BOXES(8, cd, cd_base, b0, b1, b0);
        S_BOXES(9, cd, cd_base, b1, b0, b1);
        S_BOXES(A, cd, cd_base, b0, b1, b0);
        S_BOXES(B, cd, cd_base, b1, b0, b1);
        S_BOXES(C, cd, cd_base, b0, b1, b0);
        S_BOXES(D, cd, cd_base, b1, b0, b1);
        S_BOXES(E, cd, cd_base, b0, b1, b0);
        S_BOXES(F, cd, cd_base, b1, b0, b1);

        des_vector match = v_zero;
        for (size_t i = 0; i < 32; i++) {
            match = v_or(match, v_xor(b0[i], o1[i]));
        }
        for (size_t i = 0; i < 32; i++) {
            match = v_or(match, v_xor(b1[i], o0[i]));
        }
        if (v_isnot_ones(match)) {
            uint pos = 0;
            for (uint k = 0; k < DES_VECTOR_BITS; k++) {
                pos = select(k, pos, v_and(match, v_bit(k)));
            }

            uint i = atomic_inc(result_buffer);
            result_buffer[1 + i] = (pos << BITS_GLOBAL) | cd;
        }
    }
}
