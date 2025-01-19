#pragma once
// General preprocessor functions

#define MYL_STRINGIFY(...) #__VA_ARGS__
#define MYL_ARG_STRINGIFY(x) MYL_STRINGIFY(x)

#define MYL_CONCAT(a, b) a##b
#define MYL_ARG_CONCAT(a, b) MYL_CONCAT(a, b)

// Preprocessor control flow

#define MYL_IF_0(t, f) f
#define MYL_IF_1(t, f) t
#define MYL_IF(condition, t, f) MYL_ARG_CONCAT(MYL_IF_, condition)(t, f)

// Prprocessor logical operators

#define MYL_BOOL_0 0
#define MYL_BOOL_1 1
#define MYL_BOOL_2 1
#define MYL_BOOL_3 1
#define MYL_BOOL_4 1
#define MYL_BOOL_5 1
#define MYL_BOOL_6 1
#define MYL_BOOL_7 1
#define MYL_BOOL_8 1
#define MYL_BOOL_9 1
#define MYL_BOOL_10 1
#define MYL_BOOL_11 1
#define MYL_BOOL_12 1
#define MYL_BOOL_13 1
#define MYL_BOOL_14 1
#define MYL_BOOL_15 1
#define MYL_BOOL_16 1
#define MYL_BOOL_17 1
#define MYL_BOOL_18 1
#define MYL_BOOL_19 1
#define MYL_BOOL_20 1
#define MYL_BOOL_21 1
#define MYL_BOOL_22 1
#define MYL_BOOL_23 1
#define MYL_BOOL_24 1
#define MYL_BOOL_25 1
#define MYL_BOOL_26 1
#define MYL_BOOL_27 1
#define MYL_BOOL_28 1
#define MYL_BOOL_29 1
#define MYL_BOOL_30 1
#define MYL_BOOL_31 1
#define MYL_BOOL_32 1
#define MYL_BOOL_33 1
#define MYL_BOOL_34 1
#define MYL_BOOL_35 1
#define MYL_BOOL_36 1
#define MYL_BOOL_37 1
#define MYL_BOOL_38 1
#define MYL_BOOL_39 1
#define MYL_BOOL_40 1
#define MYL_BOOL_41 1
#define MYL_BOOL_42 1
#define MYL_BOOL_43 1
#define MYL_BOOL_44 1
#define MYL_BOOL_45 1
#define MYL_BOOL_46 1
#define MYL_BOOL_47 1
#define MYL_BOOL_48 1
#define MYL_BOOL_49 1
#define MYL_BOOL_50 1
#define MYL_BOOL_51 1
#define MYL_BOOL_52 1
#define MYL_BOOL_53 1
#define MYL_BOOL_54 1
#define MYL_BOOL_55 1
#define MYL_BOOL_56 1
#define MYL_BOOL_57 1
#define MYL_BOOL_58 1
#define MYL_BOOL_59 1
#define MYL_BOOL_60 1
#define MYL_BOOL_61 1
#define MYL_BOOL_62 1
#define MYL_BOOL_63 1
#define MYL_BOOL(x) MYL_CONCAT(MYL_BOOL_, x)

#define MYL_NEGATE_0 1
#define MYL_NEGATE_1 0
#define MYL_NEGATE(boolen) MYL_CONCAT(MYL_NEGATE_, boolen)

// Variadic preprocessor functions

#define MYL_ARG_DISCARD(discard, ...) __VA_ARGS__
#define MYL_ARG_1(a1, ...) a1
#define MYL_ARG_2(a1, a2, ...) a2
#define MYL_ARG_3(a1, a2, a3, ...) a3
#define MYL_ARG_4(a1, a2, a3, a4, ...) a4
#define MYL_ARG_5(a1, a2, a3, a4, a5, ...) a5
#define MYL_ARG_6(a1, a2, a3, a4, a5, a6, ...) a6
#define MYL_ARG_7(a1, a2, a3, a4, a5, a6, a7, ...) a7
#define MYL_ARG_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a8
#define MYL_ARG_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a9

#define MYL_VA_COUNT_IMPL(\
    n0, n1, n2, n3, n4, n5, n6, n7, n8, n9,\
    n10, n11, n12, n13, n14, n15, n16, n17, n18, n19,\
    n20, n21, n22, n23, n24, n25, n26, n27, n28, n29,\
    n30, n31, n32, n33, n34, n35, n36, n37, n38, n39,\
    n40, n41, n42, n43, n44, n45, n46, n47, n48, n49,\
    n50, n51, n52, n53, n54, n55, n56, n57, n58, n59,\
    n60, n61, n62, n63, N, ...) N

#define MYL_VA_COUNT(...) MYL_VA_COUNT_IMPL(__VA_OPT__("a",) __VA_ARGS__,\
    63, 62, 61, 60,\
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50,\
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40,\
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30,\
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20,\
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10,\
    9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define MYL_VA_EMPTY(...) MYL_NEGATE(MYL_BOOL(MYL_VA_COUNT(__VA_ARGS__)))
