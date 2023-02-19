#include <myl/cpu.hpp>

#if defined(MYL_COMPILER_MSVC)
#	include <intrin.h>
#elif defined(MYL_COMPILER_CLANG) || defined(MYL_COMPILER_GCC)
#	include <cpuid.h>
#endif

#include <vector>

/// MYTodo: enum def some magic numbers
/// MYTodo: Do I have to check 0x80000001 for amd stuff?

namespace myl::cpu {
	struct cpuid_register{ /// MYTodo: Maybe make info hold this for ecx = 0 and ecx = 1
		union {
			int data[4]{ 0, 0, 0, 0 };
			struct { int eax, ebx, ecx, edx; };
		};
	};

	auto cpuid(std::vector<cpuid_register>* data, int* ids, int leaf, int sub_leaf) -> void {
#if defined(MYL_COMPILER_MSVC)
		cpuid_register cr{};
		__cpuid(cr.data, leaf);
		*ids = cr.eax;

		data->clear();
		for (int i = leaf; i != *ids; ++i) {
			__cpuidex(cr.data, i, sub_leaf);
			data->push_back(cr);
		}
#elif defined(MYL_COMPILER_CLANG) || (MYL_COMPILER_GCC)
		cpuid_register cr{};
		__get_cpuid(static_cast<unsigned int>(leaf),
			reinterpret_cast<unsigned int*>(&cr.eax),
			reinterpret_cast<unsigned int*>(&cr.ebx),
			reinterpret_cast<unsigned int*>(&cr.ecx),
			reinterpret_cast<unsigned int*>(&cr.edx));
		*ids = cr.eax;

		data->clear();
		for (unsigned int i = 0; i != *ids; ++i) {
			__get_cpuid_count(i, static_cast<unsigned int>(sub_leaf),
				reinterpret_cast<unsigned int*>(&cr.eax),
				reinterpret_cast<unsigned int*>(&cr.ebx),
				reinterpret_cast<unsigned int*>(&cr.ecx),
				reinterpret_cast<unsigned int*>(&cr.edx));
			data->push_back(cr);
		}
#else
#	error cpu.hpp: cpuid is not implemented on this compiler!
#endif
	}

	MYL_NO_DISCARD constexpr auto processor_manufacturer_id_to_vendor(const std::string_view& str) -> vendor {
		using enum vendor;
		if		(str == "AMDisbetter!")	return amd;
		else if (str == "AuthenticAMD")	return amd;
		else if (str == "CentaurHauls")	return idt;
		else if (str == "CyrixInstead")	return cyrix;
		else if (str == "GenuineIntel")	return intel;
		else if (str == "TransmetaCPU")	return transmeta;
		else if (str == "GenuineTMx86")	return transmeta;
		else if (str == "Geode by NSC")	return national_semiconductor;
		else if (str == "NexGenDriven")	return nexgen;
		else if (str == "RiseRiseRise")	return rise;
		else if (str == "SiS SiS SiS ")	return sis;
		else if (str == "UMC UMC UMC ")	return umc;
		else if (str == "VIA VIA VIA ")	return via;
		else if (str == "Vortex86 SoC")	return dmp;
		else if (str == "  Shanghai  ")	return zhaoxin;
		else if (str == "VBoxVBoxVBox")	return virtual_box;
		else if (str == "HygonGenuine")	return hygon;
		else if (str == "Genuine  RDC")	return rdc_semiconductor;
		else if (str == "E2K MACHINE ")	return mcst_elbrus;
		else if (str == "MiSTer AO486")	return ao486_cpu;
		else if (str == "GenuineAO486")	return ao486_cpu;
		else if (str == "bhyve bhyve ")	return bhyve;
		else if (str == " KVMKVMKVM  ")	return kvm;
		else if (str == "TCGTCGTCGTCG")	return qemu;
		else if (str == "Microsoft Hv")	return microsoft;
		else if (str == "MicrosoftXTA")	return microsoft;
		else if (str == " lrpepyh  vr")	return parallels; // Possible encoded incorrectly due to an endianness mismatch
		else if (str == "prl hyperv ")	return parallels; // Possible encoded incorrectly due to an endianness mismatch
		else if (str == "VMwareVMware")	return vmware;
		else if (str == "XenVMMXenVMM")	return xen_hvm;
		else if (str == "ACRNACRNACRN")	return project_acrn;
		else if (str == " QNXQVMBSQG ")	return qnx_hypervisor;
		else if (str == "VirtualApple")	return apple;
		else							return unknown;
	}

	constexpr auto vendor_to_string(vendor v) -> std::string {
		switch (v) { using enum vendor;
			case amd:						return "AMD";
			case ao486_cpu:					return "AO486 Cpu";
			case apple:						return "Apple";
			case bhyve:						return "bhyve";
			case cyrix:						return "Cyrix";
			case dmp:						return "DM&P";
			case hygon:						return "Hygon";
			case idt:						return "IDT";
			case intel:						return "Intel";
			case kvm:						return "KVM";
			case mcst_elbrus:				return "MCST Elbrus";
			case microsoft:					return "Microsoft";
			case national_semiconductor:	return "National Semiconductor";
			case nexgen:					return "NexGen";
			case parallels:					return "Parallels";
			case project_acrn:				return "Project ACRN";
			case qemu:						return "QEMU";
			case qnx_hypervisor:			return "QNX Hypervisor";
			case rdc_semiconductor:			return "RDC Semiconductor Co. Ltd.";
			case rise:						return "Rise";
			case sis:						return "SiS";
			case transmeta:					return "Transmeta";
			case umc:						return "UUMC";
			case via:						return "VIA";
			case virtual_box:				return "Virtual Box";
			case vmware:					return "VMware";
			case xen_hvm:					return "Zen HVM";
			case zhaoxin:					return "Zhaoxin";
			default:						return "Unknown";
		}
	}

	auto get_info() -> const info {
		info info{};
		std::vector<cpuid_register> cr{};
		int id_count{};

		// Leaf = 0, Sub-leaf = 0

		cpuid(&cr, &id_count, 0, 0);

		char pmi[32]{}; // Processor Manufacturer ID
		memset(pmi, 0, sizeof(pmi));
		*reinterpret_cast<int*>(pmi) = cr[0].ebx;
		*reinterpret_cast<int*>(pmi + 4) = cr[0].edx;
		*reinterpret_cast<int*>(pmi + 8) = cr[0].ecx;
		info.vendor = processor_manufacturer_id_to_vendor(pmi);

		if (id_count >= 1) {
			info.ecx_eax1_ecx0 = cr[1].ecx;
			info.edx_eax1_ecx0 = cr[1].edx;
		}

		if (id_count >= 7) {
			info.ebx_eax7_ecx0 = cr[7].ebx;
			info.ecx_eax7_ecx0 = cr[7].ecx;
			info.edx_eax7_ecx0 = cr[7].edx;
		}

		// Leaf = 0, Sub-leaf = 1

		cpuid(&cr, &id_count, 0, 1);
		if (id_count >= 7) {
			info.eax_eax0_ecx1 = cr[7].eax;
			info.edx_eax0_ecx1 = cr[7].edx;
		}

		// Leaf = 0x80000000, Sub-leaf = 0

		cpuid(&cr, &id_count, 0x80000000, 0);
		if (id_count >= 0x80000001) {
			info.ecx_eax0x80000001_ecx0 = cr[1].ecx;
			info.edx_eax0x80000001_ecx0 = cr[1].edx;
		}

		char brand_buf[64]{};
		memset(brand_buf, 0, sizeof(brand_buf));
		if (id_count >= 0x80000004) {
			memcpy(brand_buf, cr[2].data, sizeof(cpuid_register));
			memcpy(brand_buf + 16, cr[3].data, sizeof(cpuid_register));
			memcpy(brand_buf + 32, cr[4].data, sizeof(cpuid_register));
		}
		info.brand = brand_buf;

		return info;
	}
}