#pragma once

#include <boost/algorithm/string/predicate.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>
#include <boost/filesystem.hpp>

#include <map>
#include <string>
#include <vector>

namespace cinatra
{
	static const std::string _empty_str;

	class CaseMap
	{
	public:
		void add(const std::string& key, const std::string& val)
		{
			map_.emplace(key, val);
		}
		const std::string& get_val(const std::string& key) const
		{
			auto iter = map_.find(key);
			if (iter == map_.end())
			{
				return _empty_str;
			}

			return iter->second;
		}

		bool has_key(const std::string& key) const
		{
			return map_.find(key) != map_.end();
		}

		void clear()
		{
			map_.clear();
		}

		std::vector<std::pair<std::string, std::string>>
			get_all()
		{
			std::vector<std::pair<std::string, std::string>> result;
			for (auto pair : map_)
			{
				result.push_back(pair);
			}

			return result;
		}
		
		size_t size()
		{
			return map_.size();
		}
	private:
		std::map<std::string, std::string> map_;
	};

	class NcaseMultiMap
	{
	public:
		void add(const std::string& key, const std::string& val)
		{
			map_.emplace(key, val);
		}

		const std::string& get_val(const std::string& key) const
		{
			if (map_.count(key))
			{
				return map_.find(key)->second;
			}
			return _empty_str;
		}

		std::size_t get_count(const std::string& key)
		{
			return map_.count(key);
		}

		std::vector<std::string>
			get_vals(const std::string& key) const
		{
			auto range = map_.equal_range(key);
			std::vector<std::string> values;
			for (auto iter = range.first;
				iter != range.second; ++iter)
			{
				values.push_back(iter->second);
			}

			return values;
		}

		bool val_equal(const std::string& key, const std::string& str)
		{
			return get_val(key) == str;
		}
		bool val_ncase_equal(const std::string& key, const std::string& str)
		{
			return boost::iequals(get_val(key), str);
		}

		void clear()
		{
			map_.clear();
		}

		std::vector < std::pair<std::string, std::string> >
			get_all()
		{
			std::vector<std::pair<std::string, std::string>> result;
			for (auto pair : map_)
			{
				result.push_back(pair);
			}

			return result;
		}

		size_t size()
		{
			return map_.size();
		}
	private:
		struct NcaseHash
		{
			size_t operator()(const std::string& key) const
			{
				std::size_t seed = 0;
				std::locale locale;

				for (auto c : key)
				{
					boost::hash_combine(seed, std::toupper(c, locale));
				}

				return seed;
			}
		};

		struct IsKeyEqu
		{
			bool operator()(const std::string& l, const std::string& r) const
			{
				return boost::iequals(l, r);
			}
		};
		boost::unordered_multimap<std::string, std::string, NcaseHash, IsKeyEqu> map_;
	};

	inline std::string date_str()
	{
		std::string str;
		time_t last_time_t = time(0);
		tm my_tm;
#ifdef _MSC_VER
		gmtime_s(&my_tm, &last_time_t);
#else
		gmtime_r(&last_time_t, &my_tm);
#endif

		str.resize(100);

		size_t date_str_sz = strftime(&str[0], 99, "%a, %d %b %Y %H:%M:%S GMT", &my_tm);
		str.resize(date_str_sz);

		return str;
	}

	static std::map<std::string, std::string> _ext_mime_map =
	{
		{ "001", "application/x-001" },
		{ "301", "application/x-301" },
		{ "323", "text/h323" },
		{ "906", "application/x-906" },
		{ "907", "drawing/907" },
		{ "a11", "application/x-a11" },
		{ "acp", "audio/x-mei-aac" },
		{ "ai", "application/postscript" },
		{ "aif", "audio/aiff" },
		{ "aifc", "audio/aiff" },
		{ "aiff", "audio/aiff" },
		{ "anv", "application/x-anv" },
		{ "asa", "text/asa" },
		{ "asf", "video/x-ms-asf" },
		{ "asp", "text/asp" },
		{ "asx", "video/x-ms-asf" },
		{ "au", "audio/basic" },
		{ "avi", "video/avi" },
		{ "awf", "application/vnd.adobe.workflow" },
		{ "biz", "text/xml" },
		{ "bmp", "application/x-bmp" },
		{ "bot", "application/x-bot" },
		{ "c4t", "application/x-c4t" },
		{ "c90", "application/x-c90" },
		{ "cal", "application/x-cals" },
		{ "cat", "application/s-pki.seccat" },
		{ "cdf", "application/x-netcdf" },
		{ "cdr", "application/x-cdr" },
		{ "cel", "application/x-cel" },
		{ "cer", "application/x-x509-ca-cert" },
		{ "cg4", "application/x-g4" },
		{ "cgm", "application/x-cgm" },
		{ "cit", "application/x-cit" },
		{ "class", "java/*" },
		{ "cml", "text/xml" },
		{ "cmp", "application/x-cmp" },
		{ "cmx", "application/x-cmx" },
		{ "cot", "application/x-cot" },
		{ "crl", "application/pkix-crl" },
		{ "crt", "application/x-x509-ca-cert" },
		{ "csi", "application/x-csi" },
		{ "css", "text/css" },
		{ "cut", "application/x-cut" },
		{ "dbf", "application/x-dbf" },
		{ "dbm", "application/x-dbm" },
		{ "dbx", "application/x-dbx" },
		{ "dcd", "text/xml" },
		{ "dcx", "application/x-dcx" },
		{ "der", "application/x-x509-ca-cert" },
		{ "dgn", "application/x-dgn" },
		{ "dib", "application/x-dib" },
		{ "dll", "application/x-msdownload" },
		{ "doc", "application/msword" },
		{ "dot", "application/msword" },
		{ "drw", "application/x-drw" },
		{ "dtd", "text/xml" },
		{ "dwf", "Model/vnd.dwf" },
		{ "dwf", "application/x-dwf" },
		{ "dwg", "application/x-dwg" },
		{ "dxb", "application/x-dxb" },
		{ "dxf", "application/x-dxf" },
		{ "edn", "application/vnd.adobe.edn" },
		{ "emf", "application/x-emf" },
		{ "eml", "message/rfc822" },
		{ "ent", "text/xml" },
		{ "epi", "application/x-epi" },
		{ "eps", "application/x-ps" },
		{ "eps", "application/postscript" },
		{ "etd", "application/x-ebx" },
		{ "exe", "application/x-msdownload" },
		{ "fax", "image/fax" },
		{ "fdf", "application/vnd.fdf" },
		{ "fif", "application/fractals" },
		{ "fo", "text/xml" },
		{ "frm", "application/x-frm" },
		{ "g4", "application/x-g4" },
		{ "gbr", "application/x-gbr" },
		{ "gcd", "application/x-gcd" },
		{ "gif", "image/gif" },
		{ "gl2", "application/x-gl2" },
		{ "gp4", "application/x-gp4" },
		{ "hgl", "application/x-hgl" },
		{ "hmr", "application/x-hmr" },
		{ "hpg", "application/x-hpgl" },
		{ "hpl", "application/x-hpl" },
		{ "hqx", "application/mac-binhex40" },
		{ "hrf", "application/x-hrf" },
		{ "hta", "application/hta" },
		{ "htc", "text/x-component" },
		{ "htm", "text/html" },
		{ "html", "text/html" },
		{ "htt", "text/webviewhtml" },
		{ "htx", "text/html" },
		{ "icb", "application/x-icb" },
		{ "ico", "image/x-icon" },
		{ "ico", "application/x-ico" },
		{ "iff", "application/x-iff" },
		{ "ig4", "application/x-g4" },
		{ "igs", "application/x-igs" },
		{ "iii", "application/x-iphone" },
		{ "img", "application/x-img" },
		{ "ins", "application/x-internet-signup" },
		{ "isp", "application/x-internet-signup" },
		{ "IVF", "video/x-ivf" },
		{ "java", "java/*" },
		{ "jfif", "image/jpeg" },
		{ "jpe", "image/jpeg" },
		{ "jpe", "application/x-jpe" },
		{ "jpeg", "image/jpeg" },
		{ "jpg", "image/jpeg" },
		{ "jpg", "application/x-jpg" },
		{ "js", "application/x-javascript" },
		{ "jsp", "text/html" },
		{ "la1", "audio/x-liquid-file" },
		{ "lar", "application/x-laplayer-reg" },
		{ "latex", "application/x-latex" },
		{ "lavs", "audio/x-liquid-secure" },
		{ "lbm", "application/x-lbm" },
		{ "lmsff", "audio/x-la-lms" },
		{ "ls", "application/x-javascript" },
		{ "ltr", "application/x-ltr" },
		{ "m1v", "video/x-mpeg" },
		{ "m2v", "video/x-mpeg" },
		{ "m3u", "audio/mpegurl" },
		{ "m4e", "video/mpeg4" },
		{ "mac", "application/x-mac" },
		{ "man", "application/x-troff-man" },
		{ "math", "text/xml" },
		{ "mdb", "application/msaccess" },
		{ "mdb", "application/x-mdb" },
		{ "mfp", "application/x-shockwave-flash" },
		{ "mht", "message/rfc822" },
		{ "mhtml", "message/rfc822" },
		{ "mi", "application/x-mi" },
		{ "mid", "audio/mid" },
		{ "midi", "audio/mid" },
		{ "mil", "application/x-mil" },
		{ "mml", "text/xml" },
		{ "mnd", "audio/x-musicnet-download" },
		{ "mns", "audio/x-musicnet-stream" },
		{ "mocha", "application/x-javascript" },
		{ "movie", "video/x-sgi-movie" },
		{ "mp1", "audio/mp1" },
		{ "mp2", "audio/mp2" },
		{ "mp2v", "video/mpeg" },
		{ "mp3", "audio/mp3" },
		{ "mp4", "video/mp4" },
		{ "mpa", "video/x-mpg" },
		{ "mpd", "application/-project" },
		{ "mpe", "video/x-mpeg" },
		{ "mpeg", "video/mpg" },
		{ "mpg", "video/mpg" },
		{ "mpga", "audio/rn-mpeg" },
		{ "mpp", "application/-project" },
		{ "mps", "video/x-mpeg" },
		{ "mpt", "application/-project" },
		{ "mpv", "video/mpg" },
		{ "mpv2", "video/mpeg" },
		{ "mpw", "application/s-project" },
		{ "mpx", "application/-project" },
		{ "mtx", "text/xml" },
		{ "mxp", "application/x-mmxp" },
		{ "net", "image/pnetvue" },
		{ "nrf", "application/x-nrf" },
		{ "nws", "message/rfc822" },
		{ "odc", "text/x-ms-odc" },
		{ "out", "application/x-out" },
		{ "p10", "application/pkcs10" },
		{ "p12", "application/x-pkcs12" },
		{ "p7b", "application/x-pkcs7-certificates" },
		{ "p7c", "application/pkcs7-mime" },
		{ "p7m", "application/pkcs7-mime" },
		{ "p7r", "application/x-pkcs7-certreqresp" },
		{ "p7s", "application/pkcs7-signature" },
		{ "pc5", "application/x-pc5" },
		{ "pci", "application/x-pci" },
		{ "pcl", "application/x-pcl" },
		{ "pcx", "application/x-pcx" },
		{ "pdf", "application/pdf" },
		{ "pdx", "application/vnd.adobe.pdx" },
		{ "pfx", "application/x-pkcs12" },
		{ "pgl", "application/x-pgl" },
		{ "pic", "application/x-pic" },
		{ "pko", "application-pki.pko" },
		{ "pl", "application/x-perl" },
		{ "plg", "text/html" },
		{ "pls", "audio/scpls" },
		{ "plt", "application/x-plt" },
		{ "png", "image/png" },
		{ "png", "application/x-png" },
		{ "pot", "applications-powerpoint" },
		{ "ppa", "application/vs-powerpoint" },
		{ "ppm", "application/x-ppm" },
		{ "pps", "application-powerpoint" },
		{ "ppt", "applications-powerpoint" },
		{ "ppt", "application/x-ppt" },
		{ "pr", "application/x-pr" },
		{ "prf", "application/pics-rules" },
		{ "prn", "application/x-prn" },
		{ "prt", "application/x-prt" },
		{ "ps", "application/x-ps" },
		{ "ps", "application/postscript" },
		{ "ptn", "application/x-ptn" },
		{ "pwz", "application/powerpoint" },
		{ "r3t", "text/vnd.rn-realtext3d" },
		{ "ra", "audio/vnd.rn-realaudio" },
		{ "ram", "audio/x-pn-realaudio" },
		{ "ras", "application/x-ras" },
		{ "rat", "application/rat-file" },
		{ "rdf", "text/xml" },
		{ "rec", "application/vnd.rn-recording" },
		{ "red", "application/x-red" },
		{ "rgb", "application/x-rgb" },
		{ "rjs", "application/vnd.rn-realsystem-rjs" },
		{ "rjt", "application/vnd.rn-realsystem-rjt" },
		{ "rlc", "application/x-rlc" },
		{ "rle", "application/x-rle" },
		{ "rm", "application/vnd.rn-realmedia" },
		{ "rmf", "application/vnd.adobe.rmf" },
		{ "rmi", "audio/mid" },
		{ "rmj", "application/vnd.rn-realsystem-rmj" },
		{ "rmm", "audio/x-pn-realaudio" },
		{ "rmp", "application/vnd.rn-rn_music_package" },
		{ "rms", "application/vnd.rn-realmedia-secure" },
		{ "rmvb", "application/vnd.rn-realmedia-vbr" },
		{ "rmx", "application/vnd.rn-realsystem-rmx" },
		{ "rnx", "application/vnd.rn-realplayer" },
		{ "rp", "image/vnd.rn-realpix" },
		{ "rpm", "audio/x-pn-realaudio-plugin" },
		{ "rsml", "application/vnd.rn-rsml" },
		{ "rt", "text/vnd.rn-realtext" },
		{ "rtf", "application/msword" },
		{ "rtf", "application/x-rtf" },
		{ "rv", "video/vnd.rn-realvideo" },
		{ "sam", "application/x-sam" },
		{ "sat", "application/x-sat" },
		{ "sdp", "application/sdp" },
		{ "sdw", "application/x-sdw" },
		{ "sit", "application/x-stuffit" },
		{ "slb", "application/x-slb" },
		{ "sld", "application/x-sld" },
		{ "slk", "drawing/x-slk" },
		{ "smi", "application/smil" },
		{ "smil", "application/smil" },
		{ "smk", "application/x-smk" },
		{ "snd", "audio/basic" },
		{ "sol", "text/plain" },
		{ "sor", "text/plain" },
		{ "spc", "application/x-pkcs7-certificates" },
		{ "spl", "application/futuresplash" },
		{ "spp", "text/xml" },
		{ "ssm", "application/streamingmedia" },
		{ "sst", "application-pki.certstore" },
		{ "stl", "application/-pki.stl" },
		{ "stm", "text/html" },
		{ "sty", "application/x-sty" },
		{ "svg", "text/xml" },
		{ "swf", "application/x-shockwave-flash" },
		{ "tdf", "application/x-tdf" },
		{ "tg4", "application/x-tg4" },
		{ "tga", "application/x-tga" },
		{ "tif", "image/tiff" },
		{ "tif", "application/x-tif" },
		{ "tiff", "image/tiff" },
		{ "tld", "text/xml" },
		{ "top", "drawing/x-top" },
		{ "torrent", "application/x-bittorrent" },
		{ "tsd", "text/xml" },
		{ "txt", "text/plain" },
		{ "uin", "application/x-icq" },
		{ "uls", "text/iuls" },
		{ "vcf", "text/x-vcard" },
		{ "vda", "application/x-vda" },
		{ "vdx", "application/vnd.visio" },
		{ "vml", "text/xml" },
		{ "vpg", "application/x-vpeg005" },
		{ "vsd", "application/vnd.visio" },
		{ "vsd", "application/x-vsd" },
		{ "vss", "application/vnd.visio" },
		{ "vst", "application/vnd.visio" },
		{ "vst", "application/x-vst" },
		{ "vsw", "application/vnd.visio" },
		{ "vsx", "application/vnd.visio" },
		{ "vtx", "application/vnd.visio" },
		{ "vxml", "text/xml" },
		{ "wav", "audio/wav" },
		{ "wax", "audio/x-ms-wax" },
		{ "wb1", "application/x-wb1" },
		{ "wb2", "application/x-wb2" },
		{ "wb3", "application/x-wb3" },
		{ "wbmp", "image/vnd.wap.wbmp" },
		{ "wiz", "application/msword" },
		{ "wk3", "application/x-wk3" },
		{ "wk4", "application/x-wk4" },
		{ "wkq", "application/x-wkq" },
		{ "wks", "application/x-wks" },
		{ "wm", "video/x-ms-wm" },
		{ "wma", "audio/x-ms-wma" },
		{ "wmd", "application/x-ms-wmd" },
		{ "wmf", "application/x-wmf" },
		{ "wml", "text/vnd.wap.wml" },
		{ "wmv", "video/x-ms-wmv" },
		{ "wmx", "video/x-ms-wmx" },
		{ "wmz", "application/x-ms-wmz" },
		{ "wp6", "application/x-wp6" },
		{ "wpd", "application/x-wpd" },
		{ "wpg", "application/x-wpg" },
		{ "wpl", "application/-wpl" },
		{ "wq1", "application/x-wq1" },
		{ "wr1", "application/x-wr1" },
		{ "wri", "application/x-wri" },
		{ "wrk", "application/x-wrk" },
		{ "ws", "application/x-ws" },
		{ "ws2", "application/x-ws" },
		{ "wsc", "text/scriptlet" },
		{ "wsdl", "text/xml" },
		{ "wvx", "video/x-ms-wvx" },
		{ "xdp", "application/vnd.adobe.xdp" },
		{ "xdr", "text/xml" },
		{ "xfd", "application/vnd.adobe.xfd" },
		{ "xfdf", "application/vnd.adobe.xfdf" },
		{ "xhtml", "text/html" },
		{ "xls", "application/-excel" },
		{ "xls", "application/x-xls" },
		{ "xlw", "application/x-xlw" },
		{ "xml", "text/xml" },
		{ "xpl", "audio/scpls" },
		{ "xq", "text/xml" },
		{ "xql", "text/xml" },
		{ "xquery", "text/xml" },
		{ "xsd", "text/xml" },
		{ "xsl", "text/xml" },
		{ "xslt", "text/xml" },
		{ "xwd", "application/x-xwd" },
		{ "x_b", "application/x-x_b" },
		{ "x_t", "application/x-x_t" }
	};
	inline std::string content_type(const std::string& path)
	{
		std::string ext;
		auto pos = path.rfind('.');
		if (pos != std::string::npos)
		{
			ext = path.substr(pos + 1, path.size());
		}

		auto iter = _ext_mime_map.find(ext);
		if (iter != _ext_mime_map.end())
		{
			return iter->second;
		}

		return "application/octet-stream";
	}

	static std::map<int, std::string> _status_code_description =
	{
		{ 100, "Continue\r\n" },
		{ 101, "Switching Protocols\r\n" },
		{ 102, "Processing\r\n" },

		{ 200, "OK\r\n" },
		{ 201, "Created\r\n" },
		{ 202, "Accepted\r\n" },
		{ 203, "Non-Authoritative Information\r\n" },
		{ 204, "No Content\r\n" },
		{ 205, "Reset Content\r\n" },
		{ 206, "Partial Content\r\n" },
		{ 207, "Muti Status\r\n" },

		{ 300, "Multiple Choices\r\n" },
		{ 301, "Moved Permanently\r\n" },
		{ 302, "Moved Temporarily\r\n" },
		{ 303, "See Other\r\n" },
		{ 304, "Not Modified\r\n" },

		{ 400, "Bad Request\r\n" },
		{ 401, "Unauthorized\r\n" },
		{ 402, "Payment Required\r\n" },
		{ 403, "Forbidden\r\n" },
		{ 404, "Not Found\r\n" },

		{ 500, "Internal Server Error\r\n" },
		{ 501, "Not Implemented\r\n" },
		{ 502, "Bad Gateway\r\n" },
		{ 503, "Service Unavailable\r\n" },
	};

	inline std::pair<int,std::string> status_header(int status_code)
	{
		std::map<int, std::string>::const_iterator it = _status_code_description.find(status_code);
		if (it != _status_code_description.end())
		{
			return *it;
		}

		return std::make_pair(500, "Internal Server Error\r\n");
	}
}