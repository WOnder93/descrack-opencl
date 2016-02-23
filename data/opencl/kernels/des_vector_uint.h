#ifndef DES_VECTOR_UINT_H
#define DES_VECTOR_UINT_H

typedef uint des_vector_t;

#define DES_VECTOR_LEVEL 5
#define DES_VECTOR_BITS (1 << DES_VECTOR_LEVEL)

#define v_zero (des_vector_t)0u
#define v_ones (des_vector_t)0xffffffffu

#define v_and(a, b) ((a) & (b))
#define v_or(a, b)  ((a) | (b))
#define v_xor(a, b) ((a) ^ (b))
#define v_not(a)    (~(a))
#define v_andnot(a, b)  v_and(a, v_not(b))
#define v_xornot(a, b)  v_xor(a, v_not(b))

#define v_equal(a, b)       ((a) == (b))
#define v_notequal(a, b)    ((a) != (b))

#define v_is_zero(a)    v_equal(a, v_zero)
#define v_isnot_zero(a) v_notequal(a, v_zero)
#define v_is_ones(a)    v_equal(a, v_ones)
#define v_isnot_ones(a) v_notequal(a, v_ones)

#define v_mask_is_zero(a, mask)     v_is_zero(v_and(a, mask))
#define v_mask_isnot_zero(a, mask)  v_isnot_zero(v_and(a, mask))

#define v_bit(i) ((des_vector_t)0x1u << (i))

#define v_bitselect(a, b, c) bitselect(a, b, c)

#endif // DES_VECTOR_UINT_H

