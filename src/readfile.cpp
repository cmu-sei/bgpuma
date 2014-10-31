#include "readfile.h"


void ReadBGPFile(BGPDATA BGP,string file,std::ofstream &outFile )
{
	BGPDUMP *mydump;
	BGPDUMP_ENTRY *my_entry=NULL;
	struct stat buf;
	int i = 0;

	if (BGP.verbose) 
		cerr << file << "\n";
	mydump = bgpdump_open_dump(file.c_str());
	if (mydump == NULL) { 
     		int val = stat(file.c_str(),&buf);
		if (val < 0) { 
			printf ("Error statting file: %s\n",strerror(errno));
		}
		cerr << "Can not open "<< file << "\n";
		return;
	}
	do {	
		++i;
		my_entry=bgpdump_read_next(mydump);
		if(my_entry!=NULL) {
			process(my_entry,BGP,outFile);
			bgpdump_free_mem(my_entry);
		}	
	} while(mydump->eof==0);
	bgpdump_close_dump(mydump);
}


void process(BGPDUMP_ENTRY *my_entry, BGPDATA BGP,std::ofstream &outFile) 
{
	if (my_entry->type == BGPDUMP_TYPE_ZEBRA_BGP) {
		if ((my_entry->subtype == BGPDUMP_SUBTYPE_ZEBRA_BGP_MESSAGE || my_entry->subtype == BGPDUMP_SUBTYPE_ZEBRA_BGP_MESSAGE_AS4) && my_entry->body.zebra_message.type == BGP_MSG_UPDATE) {
			if (my_entry->body.zebra_message.withdraw_count)
	    			show_prefixes(my_entry->body.zebra_message.withdraw_count,my_entry->body.zebra_message.withdraw,BGP,my_entry,outFile);
		 	if (my_entry->attr != NULL && my_entry->attr->mp_info)
			{
				if (my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST] && my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST]->prefix_count)
					show_prefixes(my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST]->prefix_count,my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST]->nlri,BGP,my_entry,outFile);
			
				if (my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_MULTICAST] && my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_MULTICAST]->prefix_count)
					show_prefixes(my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_MULTICAST]->prefix_count,my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_MULTICAST]->nlri,BGP,my_entry,outFile);
	
				if (my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST_MULTICAST] && my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST_MULTICAST]->prefix_count)
					show_prefixes(my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST_MULTICAST]->prefix_count,my_entry->attr->mp_info->withdraw[AFI_IP][SAFI_UNICAST_MULTICAST]->nlri,BGP,my_entry,outFile);
	
				if (my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST] && my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST]->prefix_count)
					show_prefixes6(my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST]->prefix_count,my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST]->nlri,BGP,my_entry,outFile);
			
				if (my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_MULTICAST] && my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_MULTICAST]->prefix_count)
					show_prefixes6(my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_MULTICAST]->prefix_count,my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_MULTICAST]->nlri,BGP,my_entry,outFile);
	
				if (my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST_MULTICAST] && my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST_MULTICAST]->prefix_count)
					show_prefixes6(my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST_MULTICAST]->prefix_count,my_entry->attr->mp_info->withdraw[AFI_IP6][SAFI_UNICAST_MULTICAST]->nlri,BGP,my_entry,outFile);
			}
			
	    		if (my_entry->body.zebra_message.announce_count)
	    			show_prefixes(my_entry->body.zebra_message.announce_count,my_entry->body.zebra_message.announce,BGP,my_entry,outFile);
			if (my_entry->attr != NULL && my_entry->attr->mp_info)
			{
				if (my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST] && my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST]->prefix_count)
					show_prefixes(my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST]->prefix_count,my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST]->nlri,BGP,my_entry,outFile);
			
				if (my_entry->attr->mp_info->announce[AFI_IP][SAFI_MULTICAST] && my_entry->attr->mp_info->announce[AFI_IP][SAFI_MULTICAST]->prefix_count)
					show_prefixes(my_entry->attr->mp_info->announce[AFI_IP][SAFI_MULTICAST]->prefix_count,my_entry->attr->mp_info->announce[AFI_IP][SAFI_MULTICAST]->nlri,BGP,my_entry,outFile);

				if (my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST_MULTICAST] && my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST_MULTICAST]->prefix_count)
					show_prefixes(my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST_MULTICAST]->prefix_count,my_entry->attr->mp_info->announce[AFI_IP][SAFI_UNICAST_MULTICAST]->nlri,BGP,my_entry,outFile);

				if (my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST] && my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST]->prefix_count)
					show_prefixes6(my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST]->prefix_count,my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST]->nlri,BGP,my_entry,outFile);
			
				if (my_entry->attr->mp_info->announce[AFI_IP6][SAFI_MULTICAST] && my_entry->attr->mp_info->announce[AFI_IP6][SAFI_MULTICAST]->prefix_count)
					show_prefixes6(my_entry->attr->mp_info->announce[AFI_IP6][SAFI_MULTICAST]->prefix_count,my_entry->attr->mp_info->announce[AFI_IP6][SAFI_MULTICAST]->nlri,BGP,my_entry,outFile);

				if (my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST_MULTICAST] && my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST_MULTICAST]->prefix_count)
					show_prefixes6(my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST_MULTICAST]->prefix_count,my_entry->attr->mp_info->announce[AFI_IP6][SAFI_UNICAST_MULTICAST]->nlri,BGP,my_entry,outFile);
			}
		}
	}		
}


void show_prefixes(int count,struct prefix *prefix,BGPDATA BGP,BGPDUMP_ENTRY *entry,std::ofstream &outFile) {
    int i;
    //int rv;
    if (prefix == NULL) return;
    for(i=0;i<count;i++) {
	char cidr[128];
	int arv = 0;
	int srv = 0;

	if (prefix[i].len == 0) continue;
        sprintf(cidr,"%s/%d",inet_ntoa(prefix[i].address.v4_addr),prefix[i].len);
	if (entry->attr->aspath != NULL && BGP.asnfile.length()) {
		arv = ValidatePath(entry->attr->aspath->str,BGP);
	}
	else if (entry->attr->aspath != NULL) {
		arv = 1;
	}
	if (BGP.setfile.length()) {
		srv = ValidateSet(cidr,BGP);
	}
	else {
		srv = 1;
	}
	if (BGP.or_flag) {
		if (arv != 0 || srv != 0) 
			print_entry(cidr,entry,outFile);
	}
	else if (srv != 0 && arv != 0) {
		print_entry(cidr,entry,outFile);
	}
    }
}

void show_prefixes6(int count,struct prefix *prefix,BGPDATA BGP,BGPDUMP_ENTRY *entry,std::ofstream &outFile)
{
        int i;
        char buf[128];
	return;
        for (i=0;i<count;i++) {
		char cidr[128];
		int arv = 0;
		int srv = 0;
	        sprintf(cidr,"%s/%d",inet_ntop(AF_INET6,&prefix[i].address.v6_addr,buf,128),prefix[i].len);
		if (entry->attr->aspath != NULL && BGP.asnfile.length()) {
			arv = ValidatePath(entry->attr->aspath->str,BGP);
		}
		else if (entry->attr->aspath != NULL) {
			arv = 1;
		}
		if (BGP.setfile.length()) {
			srv = ValidateSet(cidr,BGP);
		}
		else {
			srv = 1;
		}
		if (BGP.or_flag) {
			if (arv != 0 || srv != 0) 
				print_entry(cidr,entry,outFile);
		}
		else if (srv != 0 && arv != 0) {
			print_entry(cidr,entry,outFile);
		}
	}
}

int ValidatePath(char *path, BGPDATA BGP) 
{	
	string spath = path;
	unsigned pos = spath.find_last_of(" ");
	string asn = spath.substr(pos+1);
	if (BGP.ASNList.find(asn) != BGP.ASNList.end()) {
		return 1;
	}
	return 0;
}

int ValidateSet(char *cidr, BGPDATA BGP) 
{
	skIPWildcard_t ipwild;
	int rv = skStringParseIPWildcard(&ipwild,cidr);
	if (rv != 0) {
		skAppPrintErr("Invalid IP Wildcard:  %s", skStringParseStrerror(rv));
		return 0;
	}
	rv = skIPSetCheckIPWildcard(BGP.ipset, &ipwild);
	
	return rv;

}

void print_entry(char *cidr, BGPDUMP_ENTRY *entry,std::ofstream &outFile)
{

	char prefix[BGPDUMP_ADDRSTRLEN];

	outFile << entry->time << "|";
	if (entry->body.zebra_message.withdraw_count) {
		//withdrawal
		outFile << "W|";
		switch(entry->body.zebra_message.address_family) {
			case AFI_IP6:
			inet_ntop(AF_INET6,&entry->body.zebra_message.source_ip.v6_addr,prefix,sizeof(prefix));
			outFile << prefix << "|";
			break;
			case AFI_IP:
			default:
			if (entry->body.zebra_message.source_ip.v4_addr.s_addr != 0x00000000L)
				outFile << inet_ntoa(entry->body.zebra_message.source_ip.v4_addr) << "|";
			else
				outFile << "NA|";
		}
		outFile << "AS" << print_asn(entry->body.zebra_message.source_as) << "|";
		switch(entry->body.zebra_message.address_family) {
			case AFI_IP6:
			inet_ntop(AF_INET6,&entry->body.zebra_message.destination_ip.v6_addr,prefix,sizeof(prefix));
			outFile << prefix << "|";
			break;
			case AFI_IP:
			default:
			if (entry->body.zebra_message.destination_ip.v4_addr.s_addr != 0x00000000L)
				outFile << inet_ntoa(entry->body.zebra_message.destination_ip.v4_addr) << "|";
			else
				outFile << "NA|";
		}
		outFile << "AS" << print_asn(entry->body.zebra_message.destination_as) << "|";
		outFile << cidr << std::endl;
	}
	else if ((entry->body.zebra_message.announce_count) || (entry->attr->flag & ATTR_FLAG_BIT(BGP_ATTR_MP_REACH_NLRI))) {
		//announce
		outFile << "A|";
		switch(entry->body.zebra_message.address_family) {
			case AFI_IP6:
			inet_ntop(AF_INET6,&entry->body.zebra_message.source_ip.v6_addr,prefix,sizeof(prefix));
			outFile << prefix << "|";
			break;
			case AFI_IP:
			default:
			if (entry->body.zebra_message.source_ip.v4_addr.s_addr != 0x00000000L)
				outFile << inet_ntoa(entry->body.zebra_message.source_ip.v4_addr) << "|";
			else
				outFile << "NA|";
		}
		outFile << "AS" << print_asn(entry->body.zebra_message.source_as) << "|";
		switch(entry->body.zebra_message.address_family) {
			case AFI_IP6:
			inet_ntop(AF_INET6,&entry->body.zebra_message.destination_ip.v6_addr,prefix,sizeof(prefix));
			outFile << prefix << "|";
			break;
			case AFI_IP:
			default:
			if (entry->body.zebra_message.destination_ip.v4_addr.s_addr != 0x00000000L)
				outFile << inet_ntoa(entry->body.zebra_message.destination_ip.v4_addr) << "|";
			else
				outFile << "NA|";
		}
		outFile << "AS" << print_asn(entry->body.zebra_message.destination_as) << "|";
		outFile << cidr << "|";
		
		if (entry->attr->aspath != NULL) 
			outFile << entry->attr->aspath->str;
		outFile << std::endl;
	}
}

char *print_asn(as_t asn) {
        static char asn_str[10 + 1];
        sprintf(asn_str, "%u", asn);
        return asn_str;
}
