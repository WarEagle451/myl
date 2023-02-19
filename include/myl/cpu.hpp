#pragma once
#include <myl/defines.hpp>

#include <string>

// https://en.wikipedia.org/wiki/CPUID

namespace myl::cpu {
	namespace cpuid_feature_bits {
		enum : int {
			// Processor info and features

			ecx_sse3		= 1 << 0,
			ecx_pclmulqdq	= 1 << 1,
			ecx_dtes64		= 1 << 2,
			ecx_monitor		= 1 << 3,
			ecx_ds_cpl		= 1 << 4,
			ecx_vmx			= 1 << 5,
			ecx_smx			= 1 << 6,
			ecx_est			= 1 << 7,
			ecx_tm2			= 1 << 8,
			ecx_ssse3		= 1 << 9,
			ecx_cnxt_id		= 1 << 10,
			ecx_sdbg		= 1 << 11,
			ecx_fma			= 1 << 12,
			ecx_cx16		= 1 << 13,
			ecx_xtpr		= 1 << 14,
			ecx_pdcm		= 1 << 15,
			ecx_pcid		= 1 << 17,
			ecx_dca			= 1 << 18,
			ecx_sse4_1		= 1 << 19,
			ecx_sse4_2		= 1 << 20,
			ecx_x2apic		= 1 << 21,
			ecx_movbe		= 1 << 22,
			ecx_popcnt		= 1 << 23,
			ecx_tsc_dealine	= 1 << 24,
			ecx_aes			= 1 << 25,
			ecx_xsave		= 1 << 26,
			ecx_osxsave		= 1 << 27,
			ecx_avx			= 1 << 28,
			ecx_f16c		= 1 << 29,
			ecx_rdrnd		= 1 << 30,
			ecx_hypervisor	= 1 << 31,

			edx_fpu			= 1 << 0,
			edx_vme			= 1 << 1,
			edx_de			= 1 << 2,
			edx_pse			= 1 << 3,
			edx_tsc			= 1 << 4,
			edx_msr			= 1 << 5,
			edx_pae			= 1 << 6,
			edx_mce			= 1 << 7,
			edx_cx8			= 1 << 8,
			edx_apic		= 1 << 9,
			edx_sep			= 1 << 11,
			edx_mtrr		= 1 << 12,
			edx_pge			= 1 << 13,
			edx_mca			= 1 << 14,
			edx_cmov		= 1 << 15,
			edx_pat			= 1 << 16,
			edx_pse_36		= 1 << 17,
			edx_psn			= 1 << 18,
			edx_clfsh		= 1 << 19,
			edx_ds			= 1 << 21,
			edx_acpi		= 1 << 22,
			edx_mmx			= 1 << 23,
			edx_fxsr		= 1 << 24,
			edx_sse			= 1 << 25,
			edx_sse2		= 1 << 26,
			edx_ss			= 1 << 27,
			edx_htt			= 1 << 28,
			edx_tm			= 1 << 29,
			edx_ia64		= 1 << 30,
			edx_pbe			= 1 << 31,

			// Extened features

			ebx_fsgsbase	= 1 << 0,
			ebx_unknown_1	= 1 << 1,
			ebx_sgx			= 1 << 2,
			ebx_bmi1		= 1 << 3,
			ebx_hle			= 1 << 4,
			ebx_avx2		= 1 << 5,
			ebx_unknown_6	= 1 << 6,
			ebx_smep		= 1 << 7,
			ebx_bmi2		= 1 << 8,
			ebx_erms		= 1 << 9,
			ebx_invpcid		= 1 << 10,
			ebx_rtm			= 1 << 11,
			ebx_rdt_m		= 1 << 12,
			ebx_unknown_13	= 1 << 13,
			ebx_mpx			= 1 << 14,
			ebx_rdt_a		= 1 << 15,
			ebx_avx512_f	= 1 << 16,
			ebx_avx512_dq	= 1 << 17,
			ebx_rdseed		= 1 << 18,
			ebx_adx			= 1 << 19,
			ebx_smap		= 1 << 20,
			ebx_avx512_ifma	= 1 << 21,
			ebx_clflushopt	= 1 << 23,
			ebx_clwb		= 1 << 24,
			ebx_pt			= 1 << 25,
			ebx_avx512_pf	= 1 << 26,
			ebx_avx512_er	= 1 << 27,
			ebx_avx512_cd	= 1 << 28,
			ebx_sha			= 1 << 29,
			ebx_avx512_bw	= 1 << 30,
			ebx_avx512_vl	= 1 << 31,

			ecx_prefetchwt1			= 1 << 0,
			ecx_avx512_vbmi			= 1 << 1,
			ecx_umip				= 1 << 2,
			ecx_pku					= 1 << 3,
			ecx_ospke				= 1 << 4,
			ecx_waitpkg				= 1 << 5,
			ecx_avx512_vbmi2		= 1 << 6,
			ecx_cet_ss				= 1 << 7,
			ecx_gfni				= 1 << 8,
			ecx_vaes				= 1 << 9,
			ecx_vpclmulqdq			= 1 << 10,
			ecx_avx512_vnni			= 1 << 11,
			ecx_avx512_bitalg		= 1 << 12,
			ecx_tme					= 1 << 13,
			ecx_avx512_vpopcntdq	= 1 << 14,
			ecx_la57				= 1 << 16,
			ecx_rdpid				= 1 << 22,
			ecx_kl					= 1 << 23,
			ecx_unknown_24			= 1 << 24,
			ecx_cldemote			= 1 << 25,
			ecx_movdiri				= 1 << 27,
			ecx_movdir64b			= 1 << 28,
			ecx_enqcmd				= 1 << 29,
			ecx_sgx_lc				= 1 << 30,
			ecx_pks					= 1 << 31,

			edx_sgx_keys			= 1 << 0,
			edx_avx512_4vnniw		= 1 << 2,
			edx_avx512_4fmaps		= 1 << 3,
			edx_fsrm				= 1 << 4,
			edx_uintr				= 1 << 5,
			edx_avx512_vp2intersect	= 1 << 8,
			edx_srdbs_ctrl			= 1 << 9,
			edx_mc_clear			= 1 << 10,
			edx_rtm_always_abort	= 1 << 11,
			edx_unknown_13			= 1 << 13,
			edx_serialize			= 1 << 14,
			edx_hybrid				= 1 << 15,
			edx_tsxldtrk			= 1 << 16,
			edx_pconfig				= 1 << 18,
			edx_lbr					= 1 << 19,
			edx_cet_ibt				= 1 << 20,
			edx_amx_bf16			= 1 << 22,
			edx_avx512_fp16			= 1 << 23,
			edx_amx_tile			= 1 << 24,
			edx_amx_int8			= 1 << 25,
			edx_spec_ctrl			= 1 << 26,
			edx_stibp				= 1 << 27,
			edx_l1d_flush			= 1 << 28,
			edx_unknown_29			= 1 << 29,
			edx_unknown_30			= 1 << 30,
			edx_ssbd				= 1 << 31,

			// Extend features, ECX = 1

			eax_rao_int						= 1 << 3,
			eax_avx_vnni					= 1 << 4,
			eax_avx512_bf16					= 1 << 5,
			eax_lass						= 1 << 6,
			eax_cmpccxadd					= 1 << 7,
			eax_archperfmonext				= 1 << 8,
			eax_fast_zero_rep_movsb			= 1 << 10,
			eax_fast_short_rep_stosb		= 1 << 11,
			eax_fast_short_rep_cmpsb_scasb	= 1 << 12,
			eax_fred						= 1 << 17,
			eax_lkgs						= 1 << 18,
			eax_wrmsrns						= 1 << 19,
			eax_amx_fp16					= 1 << 21,
			eax_hreset						= 1 << 22,
			eax_avx_ifma					= 1 << 23,
			eax_lam							= 1 << 26,
			eax_msrlist						= 1 << 27,

			ebx_unknown_0	= 1 << 0,

			edx_avx_vnn_int8			= 1 << 4,
			edx_avx_ne_convert			= 1 << 5,
			edx_prefetchiti				= 1 << 14,
			edx_cet_sss					= 1 << 18,

			// AMD feature flags
			/// MYTodo: add amd check in func

			ecx_lahf_lm			= 1 << 0,
			ecx_cmp_legacy		= 1 << 1,
			ecx_svm				= 1 << 2,
			ecx_extapic			= 1 << 3,
			ecx_cr8_legacy		= 1 << 4,
			ecx_abm				= 1 << 5,
			ecx_sse4a			= 1 << 6,
			ecx_misalignsse		= 1 << 7,
			ecx_3dnowprefetch	= 1 << 8,
			ecx_osvw			= 1 << 9,
			ecx_ibs				= 1 << 10,
			ecx_xop				= 1 << 11,
			ecx_skinit			= 1 << 12,
			ecx_wdt				= 1 << 13,
			ecx_lwp				= 1 << 15,
			ecx_fma4			= 1 << 16,
			ecx_tce				= 1 << 17,
			ecx_nodeid_msr		= 1 << 19,
			ecx_tbm				= 1 << 21,
			ecx_topoext			= 1 << 22,
			ecx_perfctr_core	= 1 << 23,
			ecx_perfctr_nb		= 1 << 24,
			ecx_dbx				= 1 << 26,
			ecx_perftsc			= 1 << 27,
			ecx_pcx_l2i			= 1 << 28,
			ecx_monitorx		= 1 << 29,
			ecx_addr_mask_ext	= 1 << 30,

			edx_syscall		= 1 << 11,
			edx_mp			= 1 << 19,
			edx_nx			= 1 << 20,
			edx_mmxext		= 1 << 22,
			edx_fxsr_opt	= 1 << 25,
			edx_pdpe1gb		= 1 << 26,
			edx_rdtscp		= 1 << 27,
			edx_lm			= 1 << 29,
			edx_3dnowext	= 1 << 30,
			edx_3dnow		= 1 << 31,

			// Synonyms

			ecx_lzcnt = ecx_abm, // Intel

			ebx_pqm = ebx_rdt_m, // AMD
			ebx_pqe = ebx_rdt_a, // AMD

			edx_ibrs_ibpb = edx_spec_ctrl,
		};
	}

	enum class vendor {
		amd,
		ao486_cpu,
		apple,
		bhyve,
		cyrix,
		dmp,
		hygon,
		idt,
		intel,
		kvm,
		mcst_elbrus,
		microsoft,
		national_semiconductor,
		nexgen,
		parallels,
		project_acrn,
		qemu,
		qnx_hypervisor,
		rdc_semiconductor,
		rise,
		sis,
		transmeta,
		umc,
		via,
		virtual_box,
		vmware,
		xen_hvm,
		zhaoxin,

		unknown
	};

	struct info {
		std::string brand = "";
		vendor vendor = vendor::unknown;

		int ecx_eax1_ecx0 = 0, edx_eax1_ecx0 = 0;
		int ebx_eax7_ecx0 = 0, ecx_eax7_ecx0 = 0, edx_eax7_ecx0 = 0;
		int eax_eax0_ecx1 = 0, edx_eax0_ecx1 = 0;
		int ecx_eax0x80000001_ecx0 = 0, edx_eax0x80000001_ecx0 = 0;

		// EAX == 0: Highest function parameter and manufacturer ID

		// EAX == 1: Processor info and feature bits

		MYL_NO_DISCARD constexpr auto sse3()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_sse3); }
		MYL_NO_DISCARD constexpr auto pclmulqdq()		const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_pclmulqdq); }
		MYL_NO_DISCARD constexpr auto dtes64()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_dtes64); }
		MYL_NO_DISCARD constexpr auto monitor()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_monitor); }
		MYL_NO_DISCARD constexpr auto ds_cpl()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_ds_cpl); }
		MYL_NO_DISCARD constexpr auto vmx()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_vmx); }
		MYL_NO_DISCARD constexpr auto smx()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_smx); }
		MYL_NO_DISCARD constexpr auto est()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_est); }
		MYL_NO_DISCARD constexpr auto tm2()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_tm2); }
		MYL_NO_DISCARD constexpr auto ssse3()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_ssse3); }
		MYL_NO_DISCARD constexpr auto cnxt_id()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_cnxt_id); }
		MYL_NO_DISCARD constexpr auto sdbg()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_sdbg); }
		MYL_NO_DISCARD constexpr auto fma()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_fma); }
		MYL_NO_DISCARD constexpr auto cx16()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_cx16); }
		MYL_NO_DISCARD constexpr auto xtpr()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_xtpr); }
		MYL_NO_DISCARD constexpr auto pdcm()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_pdcm); }
		MYL_NO_DISCARD constexpr auto pcid()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_pcid); }
		MYL_NO_DISCARD constexpr auto dca()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_dca); }
		MYL_NO_DISCARD constexpr auto sse4_1()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_sse4_1); }
		MYL_NO_DISCARD constexpr auto sse4_2()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_sse4_2); }
		MYL_NO_DISCARD constexpr auto x2apic()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_x2apic); }
		MYL_NO_DISCARD constexpr auto movbe()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_movbe); }
		MYL_NO_DISCARD constexpr auto popcnt()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_popcnt); }
		MYL_NO_DISCARD constexpr auto tsc_deadline()	const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_tsc_dealine); }
		MYL_NO_DISCARD constexpr auto aes()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_aes); }
		MYL_NO_DISCARD constexpr auto xsave()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_xsave); }
		MYL_NO_DISCARD constexpr auto osxsave()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_osxsave); }
		MYL_NO_DISCARD constexpr auto avx()				const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_avx); }
		MYL_NO_DISCARD constexpr auto f16c()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_f16c); }
		MYL_NO_DISCARD constexpr auto rdrnd()			const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_rdrnd); }
		MYL_NO_DISCARD constexpr auto hypervisor()		const noexcept -> bool { return static_cast<bool>(ecx_eax1_ecx0 & cpuid_feature_bits::ecx_hypervisor); }

		MYL_NO_DISCARD constexpr auto fpu()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_fpu); }
		MYL_NO_DISCARD constexpr auto vme()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_vme); }
		MYL_NO_DISCARD constexpr auto de()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_de); }
		MYL_NO_DISCARD constexpr auto pse()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_pse); }
		MYL_NO_DISCARD constexpr auto tsc()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_tsc); }
		MYL_NO_DISCARD constexpr auto msr()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_msr); }
		MYL_NO_DISCARD constexpr auto pae()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_pae); }
		MYL_NO_DISCARD constexpr auto mce()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_mce); }
		MYL_NO_DISCARD constexpr auto cx8()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_cx8); }
		MYL_NO_DISCARD constexpr auto apic()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_apic); }
		MYL_NO_DISCARD constexpr auto sep()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_sep); }
		MYL_NO_DISCARD constexpr auto mtrr()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_mtrr); }
		MYL_NO_DISCARD constexpr auto pge()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_pge); }
		MYL_NO_DISCARD constexpr auto mca()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_mca); }
		MYL_NO_DISCARD constexpr auto cmov()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_cmov); }
		MYL_NO_DISCARD constexpr auto pat()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_pat); }
		MYL_NO_DISCARD constexpr auto pse36()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_pse_36); }
		MYL_NO_DISCARD constexpr auto psn()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_psn); }
		MYL_NO_DISCARD constexpr auto clfsh()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_clfsh); }
		MYL_NO_DISCARD constexpr auto ds()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_ds); }
		MYL_NO_DISCARD constexpr auto acpi()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_acpi); }
		MYL_NO_DISCARD constexpr auto mmx()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_mmx); }
		MYL_NO_DISCARD constexpr auto fxsr()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_fxsr); }
		MYL_NO_DISCARD constexpr auto sse()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_sse); }
		MYL_NO_DISCARD constexpr auto sse2()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_sse2); }
		MYL_NO_DISCARD constexpr auto ss()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_ss); }
		MYL_NO_DISCARD constexpr auto htt()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_htt); }
		MYL_NO_DISCARD constexpr auto tm()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_tm); }
		MYL_NO_DISCARD constexpr auto ia64()	const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_ia64); }
		MYL_NO_DISCARD constexpr auto pbe()		const noexcept -> bool { return static_cast<bool>(edx_eax1_ecx0 & cpuid_feature_bits::edx_pbe); }

		// EAX == 2: Cache and TLB descriptor information

		// EAX == 3: Processor serial number

		// EAX == 4, EAX == Bh: Intel thread/core and cache topology

		// EAX == 5: ???

		// EAX == 6: Thermal and power management

		// EAX == 7, ECX == 0: Extended features

		MYL_NO_DISCARD constexpr auto fsgsbase()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_fsgsbase); }
		MYL_NO_DISCARD constexpr auto sgx()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_sgx); }
		MYL_NO_DISCARD constexpr auto bmi1()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_bmi1); }
		MYL_NO_DISCARD constexpr auto hle()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_hle); }
		MYL_NO_DISCARD constexpr auto avx2()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx2); }
		MYL_NO_DISCARD constexpr auto smep()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_smep); }
		MYL_NO_DISCARD constexpr auto bmi2()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_bmi2); }
		MYL_NO_DISCARD constexpr auto erms()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_erms); }
		MYL_NO_DISCARD constexpr auto invpcid()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_invpcid); }
		MYL_NO_DISCARD constexpr auto rtm()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_rtm); }
		MYL_NO_DISCARD constexpr auto rdt_m()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_rdt_m) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto pqm()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_pqm) && vendor == vendor::amd; }
		MYL_NO_DISCARD constexpr auto mpx()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_mpx) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto rdt_a()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_rdt_a) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto pqe()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_pqe) && vendor == vendor::amd; }
		MYL_NO_DISCARD constexpr auto avx512_f()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_f); }
		MYL_NO_DISCARD constexpr auto avx512_dq()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_dq); }
		MYL_NO_DISCARD constexpr auto rdseed()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_rdseed); }
		MYL_NO_DISCARD constexpr auto adx()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_adx) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto smap()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_smap); }
		MYL_NO_DISCARD constexpr auto avx512_ifma()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_ifma); }
		MYL_NO_DISCARD constexpr auto clflushopt()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_clflushopt); }
		MYL_NO_DISCARD constexpr auto clwb()		const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_clwb); }
		MYL_NO_DISCARD constexpr auto pt()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_pt) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto avx512_pf()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_pf); }
		MYL_NO_DISCARD constexpr auto avx512_er()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_er); }
		MYL_NO_DISCARD constexpr auto avx512_cd()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_cd); }
		MYL_NO_DISCARD constexpr auto sha()			const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_sha); }
		MYL_NO_DISCARD constexpr auto avx512_bw()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_bw); }
		MYL_NO_DISCARD constexpr auto avx512_vl()	const noexcept -> bool { return static_cast<bool>(ebx_eax7_ecx0 & cpuid_feature_bits::ebx_avx512_vl); }

		MYL_NO_DISCARD constexpr auto prefetchwt1()			const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_prefetchwt1); }
		MYL_NO_DISCARD constexpr auto avx512_vbmi()			const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_avx512_vbmi); }
		MYL_NO_DISCARD constexpr auto umip()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_umip); }
		MYL_NO_DISCARD constexpr auto pku()					const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_pku); }
		MYL_NO_DISCARD constexpr auto ospke()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_ospke); }
		MYL_NO_DISCARD constexpr auto waitpkg()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_waitpkg); }
		MYL_NO_DISCARD constexpr auto avx512_vbmi2()		const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_avx512_vbmi2); }
		MYL_NO_DISCARD constexpr auto cet_ss()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_cet_ss); }
		MYL_NO_DISCARD constexpr auto gfni()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_gfni); }
		MYL_NO_DISCARD constexpr auto vaes()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_vaes); }
		MYL_NO_DISCARD constexpr auto vpclmulqdq()			const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_vpclmulqdq); }
		MYL_NO_DISCARD constexpr auto avx512_vnni()			const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_avx512_vnni); }
		MYL_NO_DISCARD constexpr auto avx512_bitalg()		const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_avx512_bitalg); }
		MYL_NO_DISCARD constexpr auto tme()					const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_tme); }
		MYL_NO_DISCARD constexpr auto avx512_vpopcntdq()	const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_avx512_vpopcntdq); }
		MYL_NO_DISCARD constexpr auto la57()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_la57); }
		MYL_NO_DISCARD constexpr auto rdpid()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_rdpid); }
		MYL_NO_DISCARD constexpr auto kl()					const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_kl); }
		MYL_NO_DISCARD constexpr auto cldemote()			const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_cldemote); }
		MYL_NO_DISCARD constexpr auto movdiri()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_movdiri); }
		MYL_NO_DISCARD constexpr auto movdir64b()			const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_movdir64b); }
		MYL_NO_DISCARD constexpr auto enqcmd()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_enqcmd); }
		MYL_NO_DISCARD constexpr auto sgx_lc()				const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_sgx_lc); }
		MYL_NO_DISCARD constexpr auto pks()					const noexcept -> bool { return static_cast<bool>(ecx_eax7_ecx0 & cpuid_feature_bits::ecx_pks); }

		MYL_NO_DISCARD constexpr auto sgx_keys()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::ebx_sgx) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto avx512_4vnniw()			const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_avx512_4vnniw); }
		MYL_NO_DISCARD constexpr auto avx512_4fmaps()			const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_avx512_4fmaps); }
		MYL_NO_DISCARD constexpr auto fsrm()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_fsrm); }
		MYL_NO_DISCARD constexpr auto uintr()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_uintr); }
		MYL_NO_DISCARD constexpr auto avx512_vp2intersect()		const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_avx512_vp2intersect); }
		MYL_NO_DISCARD constexpr auto srdbs_ctrl()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_srdbs_ctrl); }
		MYL_NO_DISCARD constexpr auto mc_clear()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_mc_clear); }
		MYL_NO_DISCARD constexpr auto rtm_always_abort()		const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_rtm_always_abort); }
		MYL_NO_DISCARD constexpr auto serialize()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_serialize); }
		MYL_NO_DISCARD constexpr auto hybrid()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_hybrid); }
		MYL_NO_DISCARD constexpr auto tsxldtrk()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_tsxldtrk); }
		MYL_NO_DISCARD constexpr auto pconfig()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_pconfig); }
		MYL_NO_DISCARD constexpr auto lbr()						const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_lbr); }
		MYL_NO_DISCARD constexpr auto cet_ibt()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_cet_ibt); }
		MYL_NO_DISCARD constexpr auto amx_bf16()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_amx_bf16); }
		MYL_NO_DISCARD constexpr auto avx512_fp16()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_avx512_fp16); }
		MYL_NO_DISCARD constexpr auto amx_tile()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_amx_tile); }
		MYL_NO_DISCARD constexpr auto amx_int8()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_amx_int8); }
		MYL_NO_DISCARD constexpr auto spec_ctrl()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_spec_ctrl); }
		MYL_NO_DISCARD constexpr auto stibp()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_stibp); }
		MYL_NO_DISCARD constexpr auto l1d_flush()				const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_l1d_flush); }
		MYL_NO_DISCARD constexpr auto ssbd()					const noexcept -> bool { return static_cast<bool>(edx_eax7_ecx0 & cpuid_feature_bits::edx_ssbd); }
		
		// EAX == 7, ECX == 1: Extended features

		MYL_NO_DISCARD constexpr auto rao_int()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_rao_int); }
		MYL_NO_DISCARD constexpr auto avx_vnni()					const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_avx_vnni); }
		MYL_NO_DISCARD constexpr auto avx512_bf16()					const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_avx512_bf16); }
		MYL_NO_DISCARD constexpr auto lass()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_lass); }
		MYL_NO_DISCARD constexpr auto cmpccxadd()					const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_cmpccxadd); }
		MYL_NO_DISCARD constexpr auto archperfmonext()				const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_archperfmonext); }
		MYL_NO_DISCARD constexpr auto fast_zero_rep_movsb()			const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_fast_zero_rep_movsb); }
		MYL_NO_DISCARD constexpr auto fast_short_rep_stosb()		const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_fast_short_rep_stosb); }
		MYL_NO_DISCARD constexpr auto fast_short_rep_cmpsb_scasb()	const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_fast_short_rep_cmpsb_scasb); }
		MYL_NO_DISCARD constexpr auto fred()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_fred); }
		MYL_NO_DISCARD constexpr auto lkgs()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_lkgs); }
		MYL_NO_DISCARD constexpr auto wrmsrns()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_wrmsrns); }
		MYL_NO_DISCARD constexpr auto amx_fp16()					const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_amx_fp16); }
		MYL_NO_DISCARD constexpr auto hreset()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_hreset); }
		MYL_NO_DISCARD constexpr auto avx_ifma()					const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_avx_ifma); }
		MYL_NO_DISCARD constexpr auto lam()							const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_lam); }
		MYL_NO_DISCARD constexpr auto msrlist()						const noexcept -> bool { return static_cast<bool>(eax_eax0_ecx1 & cpuid_feature_bits::eax_msrlist); }

		MYL_NO_DISCARD constexpr auto avx_vnn_int8()	const noexcept -> bool { return static_cast<bool>(edx_eax0_ecx1 & cpuid_feature_bits::edx_avx_vnn_int8); }
		MYL_NO_DISCARD constexpr auto avx_ne_convert()	const noexcept -> bool { return static_cast<bool>(edx_eax0_ecx1 & cpuid_feature_bits::edx_avx_ne_convert); }
		MYL_NO_DISCARD constexpr auto prefetchiti()		const noexcept -> bool { return static_cast<bool>(edx_eax0_ecx1 & cpuid_feature_bits::edx_prefetchiti); }
		MYL_NO_DISCARD constexpr auto cet_sss()			const noexcept -> bool { return static_cast<bool>(edx_eax0_ecx1 & cpuid_feature_bits::edx_cet_sss); }

		// EAX == 0Dh, ECX == 1: CPUID feature bits
		
		// EAX == 12h, ECX == 0: SGX leaf functions
		
		// EAX == 14h, ECX == 0: CPUID feature bits
		
		// EAX == 19h: CPUID feature bits
		
		// EAX == 80000000h: Highest extended function implemented
		
		// EAX == 80000001h: Extended processor indo and feature bits
		
		MYL_NO_DISCARD constexpr auto lahf_lm()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_lahf_lm); }
		MYL_NO_DISCARD constexpr auto cmp_legacy()		const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_cmp_legacy); }
		MYL_NO_DISCARD constexpr auto svm()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_svm); }
		MYL_NO_DISCARD constexpr auto extapic()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_extapic); }
		MYL_NO_DISCARD constexpr auto cr8_legacy()		const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_cr8_legacy); }
		MYL_NO_DISCARD constexpr auto lzcnt()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_lzcnt) && vendor == vendor::intel; }
		MYL_NO_DISCARD constexpr auto abm()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_abm) && vendor == vendor::amd; }
		MYL_NO_DISCARD constexpr auto sse4a()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_sse4a); }
		MYL_NO_DISCARD constexpr auto misalignsse()		const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_misalignsse); }
		MYL_NO_DISCARD constexpr auto _3dnowprefetch()	const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_3dnowprefetch) && vendor == vendor::amd; }
		MYL_NO_DISCARD constexpr auto osvw()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_osvw); }
		MYL_NO_DISCARD constexpr auto ibs()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_ibs); }
		MYL_NO_DISCARD constexpr auto xop()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_xop); }
		MYL_NO_DISCARD constexpr auto skinit()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_skinit); }
		MYL_NO_DISCARD constexpr auto wdt()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_wdt); }
		MYL_NO_DISCARD constexpr auto lwp()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_lwp); }
		MYL_NO_DISCARD constexpr auto fma4()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_fma4); }
		MYL_NO_DISCARD constexpr auto tce()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_tce); }
		MYL_NO_DISCARD constexpr auto nodeid_msr()		const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_nodeid_msr); }
		MYL_NO_DISCARD constexpr auto tbm()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_tbm); }
		MYL_NO_DISCARD constexpr auto topoext()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_topoext); }
		MYL_NO_DISCARD constexpr auto perfctr_core()	const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_perfctr_core); }
		MYL_NO_DISCARD constexpr auto perfctr_nb()		const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_perfctr_nb); }
		MYL_NO_DISCARD constexpr auto dbx()				const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_dbx); }
		MYL_NO_DISCARD constexpr auto perftsc()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_perftsc); }
		MYL_NO_DISCARD constexpr auto pcx_l2i()			const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_pcx_l2i); }
		MYL_NO_DISCARD constexpr auto monitorx()		const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_monitorx); }
		MYL_NO_DISCARD constexpr auto addr_mask_ext()	const noexcept -> bool { return static_cast<bool>(ecx_eax0x80000001_ecx0 & cpuid_feature_bits::ecx_addr_mask_ext); }

		MYL_NO_DISCARD constexpr auto syscall()		const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_syscall); }
		MYL_NO_DISCARD constexpr auto mp()			const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_mp); }
		MYL_NO_DISCARD constexpr auto nx()			const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_nx); }
		MYL_NO_DISCARD constexpr auto mmxext()		const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_mmxext); }
		MYL_NO_DISCARD constexpr auto fxsr_opt()	const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_fxsr_opt); }
		MYL_NO_DISCARD constexpr auto pdpe1gb()		const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_pdpe1gb); }
		MYL_NO_DISCARD constexpr auto rdtscp()		const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_rdtscp); }
		MYL_NO_DISCARD constexpr auto lm()			const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_lm); }
		MYL_NO_DISCARD constexpr auto _3dnowext()	const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_3dnowext) && vendor == vendor::amd; }
		MYL_NO_DISCARD constexpr auto _3dnow()		const noexcept -> bool { return static_cast<bool>(edx_eax0x80000001_ecx0 & cpuid_feature_bits::edx_3dnow) && vendor == vendor::amd; }

		// EAX == 80000002h, 80000003h, 80000004h: Processor brand string
		
		// EAX == 80000005h: L1 Cache and TLB identifiers
		
		// EAX == 80000006h: Extended L2 cache features
		
		// EAX == 80000007h: Advanced power management information
		
		// EAX == 80000008h: Virtual and physical address sizes
		
		// EAX == 8000001Fh: Encrypted memory capabilities
		
		// EAX == 80000021h: Extended feature identification 2
		
		// EAX == 8FFFFFFFh: AMD easter egg
	};

	MYL_API MYL_NO_DISCARD constexpr auto vendor_to_string(vendor) -> std::string;

	MYL_API MYL_NO_DISCARD auto get_info() -> const info;
}