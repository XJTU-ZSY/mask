#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
using namespace std;
typedef unsigned int	uint32_t;
typedef unsigned short	uint16_t;
typedef unsigned char	uint8_t;

typedef struct {
	uint32_t DataIP[2];
	uint32_t MaskIP[2];
	uint32_t DataPort[2];
	uint32_t MaskPort[2];
	uint8_t DataProtocol;
	uint8_t MaskProtocol;
	uint32_t result;
}T;

typedef struct {
	uint16_t Data;
	uint16_t Mask;
}DM;
typedef struct {
	uint32_t Data;
	uint32_t Mask;
}DM2;

void Tcopy(T &t1, T &t2) { //将t1赋值给t2
	for (int i = 0; i < 2; i++) {
		t2.DataIP[i] = t1.DataIP[i];
		t2.MaskIP[i] = t1.MaskIP[i];
		t2.DataPort[i] = t1.DataPort[i];
		t2.MaskPort[i] = t1.MaskPort[i];
	}
	t2.DataProtocol = t1.DataProtocol;
	t2.MaskProtocol = t1.MaskProtocol;
	t2.result = t1.result;
}

//vector<DM> DealPort_v1(unsigned short port1, unsigned short port2) {
//	vector<DM> vdm;
//	vector<DM> vdm1;
//	vector<DM> vdm2;
//	DM dm;
//	uint16_t m = 0xffff;
//	uint16_t MidPort = (port1 + port2) / 2;
//	uint16_t Distance = MidPort - port1;
//	uint16_t n = log2(Distance) + 1;
//	if (port2 == port1) {
//		dm.Mask = m;
//		dm.Data = port1;
//		vdm.push_back(dm);
//		return vdm;
//	}
//	if (((((((port1 + port2) / 2) & (m << (n + 1))) + pow(2, n + 1) - 1) > port2) || ((((port1 + port2) / 2) & (m << (n + 1))) < port1))) {
//		n = n - 1;
//		if (((((((port1 + port2) / 2) & (m << (n + 1))) + pow(2, n + 1) - 1) > port2) || ((((port1 + port2) / 2) & (m << (n + 1))) < port1))) {
//			n = n - 1;
//		}
//	}
//	dm.Mask = m << (n + 1);
//	dm.Data = MidPort & dm.Mask;
//	vdm.push_back(dm);
//	if ((dm.Data + pow(2, n + 1) - 1) < (port2 - 1)) {
//		vdm1 = DealPort_v1((dm.Data + pow(2, n + 1) - 1) + 1, port2);
//	}
//	if (dm.Data > (port1 + 1)) {
//		vdm2 = DealPort_v1(port1, dm.Data - 1);
//	}
//	vdm.insert(vdm.end(), vdm1.begin(), vdm1.end());
//	vdm.insert(vdm.end(), vdm2.begin(), vdm2.end());
//	return vdm;
//}
//
//vector<uint16_t> PreDeal(unsigned int port1, unsigned int port2) {
//	vector<uint16_t> p;
//	bool flag = 0;
//	uint16_t m = 0xffff;
//	uint16_t f = 0x8000;
//	if (port2 - port1 == 1) {
//		if (port1 % 2 == 0) {
//			p.push_back(0);
//			p.push_back(port1);
//			p.push_back(port2);
//			return p;
//		}
//		else {
//			p.push_back(1);
//			p.push_back(port1 - 1);
//			p.push_back(port2 - 1);
//			return p;
//		}
//	}
//	uint16_t MidPort = (port1 + port2) / 2;
//	uint16_t Distance = MidPort - port1;
//	uint16_t n = log2(Distance) + 1;
//	if (((((((port1 + port2) / 2) & (m << (n + 1))) + pow(2, n + 1) - 1) > port2) || ((((port1 + port2) / 2) & (m << (n + 1))) < port1))) {
//		n = n - 1;
//		if (((((((port1 + port2) / 2) & (m << (n + 1))) + pow(2, n + 1) - 1) > port2) || ((((port1 + port2) / 2) & (m << (n + 1))) < port1))) {
//			n = n - 1;
//		}
//	}
//
//	uint16_t Data = ((port1 + port2) / 2) & (m << (n + 1));
//	uint16_t d;
//	d = port2 - (Data + pow(2, n + 1) - 1);
//	if (d <= port1) {
//		p.push_back(d);
//		p.push_back(port1 - d);
//		p.push_back(port2 - d);
//		return p;
//	}
//	d = Data - port1;
//	if (d <= 65535 - port2) {
//		p.push_back(d | f);
//		p.push_back(port1 + d);
//		p.push_back(port2 + d);
//		return p;
//	}
//	p.push_back(0);
//	p.push_back(port1);
//	p.push_back(port2);
//	return p;
//}
//vector<uint16_t> DealPort_v2(unsigned short port1, unsigned short port2) {
//	vector<uint16_t> p; //data mask left right
//	uint16_t m = 0xffff;
//	uint16_t f = 0x8000;
//	uint16_t MidPort = (port1 + port2) / 2; //
//	uint16_t Distance = MidPort - port1;
//	uint16_t n = log2(Distance) + 1; //
//	if (port2 == port1) {
//		p.push_back(port1);
//		p.push_back(m);
//		p.push_back(0);
//		p.push_back(0);
//		return p;
//	}
//	if (((((((port1 + port2) / 2) & (m << (n + 1))) + pow(2, n + 1) - 1) > port2) || ((((port1 + port2) / 2) & (m << (n + 1))) < port1))) {
//		n = n - 1;
//		if (pow(2, n) > Distance) {
//			if (((((((port1 + port2) / 2) & (m << (n + 1))) + pow(2, n + 1) - 1) > port2) || ((((port1 + port2) / 2) & (m << (n + 1))) < port1))) {
//				n = n - 1;
//			}
//		}
//
//	}
//	uint16_t Mask = m << (n + 1);
//	uint16_t Data = MidPort & m << (n + 1);
//	uint16_t left = Data - port1;
//	uint16_t right = port2 - (Data + pow(2, n + 1) - 1);
//	p.push_back(Data);
//	p.push_back(Mask);
//	p.push_back(left | f);
//	p.push_back(right);
//	return p;
//}
vector<uint16_t> DealPort_v3(unsigned short port1, unsigned short port2) {
	vector<uint16_t> p; //data mask left right
	uint16_t m = 0xffff;
	uint16_t f = 0x8000;
	uint16_t MidPort = (port1 + port2) / 2; //
	uint16_t Distance = port2 - port1;
	uint16_t n = log2(Distance); //
	if (port2 == port1) {
		p.push_back(port1);
		p.push_back(m);
		p.push_back(0);
		return p;
	}
	if (port2 - port1 == 1) {
		if (port1 % 2 == 0) {
			p.push_back(port1);
			p.push_back(m<<1);
			p.push_back(0);
		}
		else {
			p.push_back(port1);
			p.push_back(m << 1);
			p.push_back(1);
		}
		return p;
	}
	uint16_t Mask = m << n;
	uint16_t Data = MidPort & (m << n);
	p.push_back(Data);
	p.push_back(Mask);
	//if (Data >= port1 && (Data + pow(2, n) - 1) <= port2) {		// 第一种情况：覆盖范围落在两个端口之间
	//	uint16_t left = Data - port1;
	//	uint16_t right = port2 - (Data + pow(2, n) - 1);
	//	p.push_back(left | f);
	//	p.push_back(right);
	//}	
	//else if (Data < port1 ) {		// 第二种情况：覆盖范围超左边界
	//	uint16_t left = port1 - Data;
	//	uint16_t right = port2 - (Data + pow(2, n) - 1);
	//	p.push_back(left);
	//	p.push_back(right);
	//}
	//else if ((Data + pow(2, n) - 1) > port2) {		// 第三种情况：覆盖范围超右边界
	//	uint16_t left = Data - port1;
	//	uint16_t right = (Data + pow(2, n) - 1) - port2;
	//	p.push_back(left | f);
	//	p.push_back(right | f);
	//}
	if (Data >= port1 && (Data + pow(2, n) - 1) <= port2) {		// 第一种情况：覆盖范围落在两个端口之间
		short left = port1 - Data;
		short right = port2 - (Data + pow(2, n) - 1);
		p.push_back(left);
		p.push_back(right);
	}
	else if (Data < port1) {		// 第二种情况：覆盖范围超左边界
		short left = port1 - Data;
		short right = port2 - (Data + pow(2, n) - 1);
		p.push_back(left);
		p.push_back(right);
	}
	else if ((Data + pow(2, n) - 1) > port2) {		// 第三种情况：覆盖范围超右边界
		short left = port1 - Data;
		short right = port2 - (Data + pow(2, n) - 1);
		p.push_back(left);
		p.push_back(right);
	}
	return p;
}

void RuleDeal(vector<T> &TFile, vector<uint32_t> IPBook) {
	uint32_t Ip[2][4], IpPrefix[2];
	uint32_t Port[2][2];
	uint32_t Protocol, ProtocolPrefix;
	uint32_t result;
	T t;
	scanf("%d.%d.%d.%d/%d %d.%d.%d.%d/%d %d:%d %d:%d 0x%x/0x%x %d", &Ip[0][0], &Ip[0][1], &Ip[0][2], &Ip[0][3], &IpPrefix[0],
		&Ip[1][0], &Ip[1][1], &Ip[1][2], &Ip[1][3], &IpPrefix[1], &Port[0][0], &Port[0][1], &Port[1][0], &Port[1][1],
		&Protocol, &ProtocolPrefix, &result);
	for (uint32_t i = 0; i < 2; i++) {
		t.MaskIP[i] = 0xffffffff << (32 - IpPrefix[i]);
		t.DataIP[i] = t.MaskIP[i] & ((Ip[i][0] << 24) | (Ip[i][1] << 16) | (Ip[i][2] << 8) | (Ip[i][3]));
	}
	t.MaskProtocol = ProtocolPrefix;
	t.DataProtocol = Protocol;
	t.result = result;											  //  0	   1    2    3
	vector<uint16_t> vdm1 = DealPort_v3(Port[0][0], Port[0][1]);  //data mask left right
	vector<uint16_t> vdm2 = DealPort_v3(Port[1][0], Port[1][1]);
	for (uint8_t i = 0; i < vdm1.size()-2; i++) {
		for (uint8_t j = 0; j < vdm2.size() - 2; j++) {
			T t_temp;
			Tcopy(t, t_temp);
			t_temp.DataPort[0] = (vdm1[i + 2] << 16) | vdm1[0];
			t_temp.MaskPort[0] = 0xffff0000 | vdm1[1]; 
			t_temp.DataPort[1] = (vdm2[j + 2] << 16) | vdm2[0];
			t_temp.MaskPort[1] = 0xffff0000 | vdm2[1]; 
			TFile.push_back(t_temp);
		}
	}
}

int MessageMatch(vector<T> &TFile) {
	uint32_t Ip[2][4];
	uint32_t Port[2];
	uint32_t Protocol;
	//⑴、读取输入的报文并将其赋值给各个变量
	scanf("%d.%d.%d.%d %d.%d.%d.%d %d %d %d", &Ip[0][0], &Ip[0][1], &Ip[0][2], &Ip[0][3],
		&Ip[1][0], &Ip[1][1], &Ip[1][2], &Ip[1][3], &Port[0], &Port[1], &Protocol);
	//(2)、合成目的IP地址和源IP地址
	uint32_t ipPurpose = (Ip[0][0] << 24) | (Ip[0][1] << 16) | (Ip[0][2] << 8) | (Ip[0][3]);
	uint32_t ipSource = (Ip[1][0] << 24) | (Ip[1][1] << 16) | (Ip[1][2] << 8) | (Ip[1][3]);
	T t;
	bool flag = 0;  //端口匹配标志 1=>不匹配 0=>匹配
	size_t len = TFile.size(); //内存中总的data、mask对
	for (size_t i = 0; i < len; i++) {
		t = TFile[i];
		flag = 0;
		if ((ipPurpose & t.MaskIP[0]) == t.DataIP[0] && (ipSource & t.MaskIP[1]) == t.DataIP[1]) {  //ip匹配
			uint32_t port1 = (t.DataPort[0] & 0xffff0000) | ((Port[0] - (t.DataPort[0] >> 16)) & 0xffff);
			uint32_t port2 = (t.DataPort[1] & 0xffff0000) | ((Port[1] - (t.DataPort[1] >> 16)) & 0xffff);
			if (((port1 & t.MaskPort[0]) == (t.DataPort[0] & t.MaskPort[0])) && ((port2 & t.MaskPort[1]) == (t.DataPort[1] & t.MaskPort[1]))) {
				if ((Protocol & t.MaskProtocol) == t.DataProtocol)  //Protocol匹配
					return t.result;
			}
		}
	}
	return 0;
}
int Result(vector<uint32_t> &ret) {
	size_t len = ret.size();
	uint32_t result;
	bool flag = 0;
	for (size_t i = 0; i < len; i++) {
		scanf("%d", &result);
		if (result != ret[i]) {
			cout << "不匹配" << endl;
			return -1;
		}
	}
	cout << "匹配" << endl;
	return 0;
}
int main(int argc, char* argv[])
{
	//vector<uint16_t> vdm = DealPort_v3(0,65534);
	//vector<DM2> DM;
	//uint32_t jj = 0;
	//for (uint8_t i = 0; i < vdm.size() - 2; i++) {
	//	    DM2 t_temp;
	//		t_temp.Data = (vdm[i + 2] << 16) | vdm[0];
	//		t_temp.Mask = 0xffff0000 | vdm[1];
	//		DM.push_back(t_temp);
	//}
	//for (uint32_t j = 1; j < 65536; j++) {
	//	uint32_t i = 0;
	//	for ( i = 0; i < DM.size(); i++) {
	//		DM2 DM3 = DM[i];
	//		uint32_t port = (DM3.Data & 0xffff0000) | ((j - (DM3.Data >> 16)) & 0xffff);
	//		if ((port & DM3.Mask) == (DM3.Data & DM3.Mask))break;
	//	}
	//	if (i == DM.size()) { 
	//		if (jj != j - 1)	printf("************************\n");
	//		printf("%d\n", j);
	//		jj = j;
	//	}
	//}
	vector<uint32_t> IPBook;
	vector<T> TFile;
	uint32_t NumRule;//总的规则数量
	scanf("%d", &NumRule);
	clock_t start = clock();
	for (uint32_t i = 0; i < NumRule; i++) {
		RuleDeal(TFile, IPBook);
	}
	vector<uint32_t> ret;
	uint32_t NumMes;//总的规则数量
	scanf("%d", &NumMes); //总的报文数量
	for (uint32_t i = 0; i < NumMes; i++) {
		ret.push_back(MessageMatch(TFile));
	}
	size_t len = TFile.size();
	printf("32 32 32 32 8 %d\n", len);
	//for (size_t i = 0; i < len; i++) {
	//	T t = TFile[i];
	//	printf("data:0x%x 0x%x 0x%x 0x%x 0x%x %d\nmask:0x%x 0x%x 0x%x 0x%x 0x%x\n", t.DataIP[0], t.DataIP[1], t.DataPort[0], t.DataPort[1],  //8042
	//		t.DataProtocol, t.result,t.MaskIP[0], t.MaskIP[1], t.MaskPort[0], t.MaskPort[1], t.MaskProtocol);
	//}
	//len = ret.size();
	//for (size_t i = 0; i < len; i++) {
	//	printf("%d\n", ret[i]);
	//}
	Result(ret);
	clock_t ends = clock();
	cout << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC << endl;
	return 0;
}