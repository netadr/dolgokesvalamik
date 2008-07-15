#ifndef _file_h_
#define _file_h_

#include "utils/misc.h"
#include "containers/string.h"
#include <sys/stat.h>

namespace file
{
	class file
	{
	public:
		file();
		file(const char* i_name, const char* i_attributes);
		~file();
		void open(const char* i_name, const char* i_attributes);
		void close();

		bool read_line(ctr::string& o_line) const;
		void write_line(const char* i_line) const;
		unsigned read_bytes(char* o_bytes, unsigned i_numbytes) const;
		void write_bytes(const char* i_bytes, unsigned i_numbytes) const;

		unsigned size() const;

		bool opened() const;
	private:
		file(const file&);
		void operator=(const file&);
		FILE* m_handle;
		ctr::string m_name;
		unsigned m_size;
	};


	MLINLINE file::file()
	{
		m_handle=NULL;
		m_size=0;
	}

	MLINLINE file::file(const char* i_name,const char* i_attributes):
	m_handle(NULL)
	{
		open(i_name,i_attributes);
	}

	MLINLINE void file::open(const char* i_name, const char* i_attributes)
	{
		if (m_handle)
			close();

		m_handle=fopen(i_name,i_attributes);
		if (m_handle)
		{
			struct stat statistics;
			fstat(_fileno(m_handle),&statistics);
			m_size=statistics.st_size;
			m_name=i_name;
		}
	}

	MLINLINE void file::close()
	{
		if (!m_handle)
			return;

		fclose(m_handle);
		m_handle=NULL;
		m_name="";
		m_size=0;
	}

	MLINLINE file::~file()
	{
		if (m_handle)
			fclose(m_handle);
	}

	MLINLINE bool file::read_line(ctr::string& o_line) const
	{
		char line[16384];

		if (fgets(line,16383,m_handle))
		{
			int len=(int)strlen(line)-1;

			while (len>=0)
			{
				if (line[len]==13 || line[len]==10)
				{
					line[len--]=0;
				}
				else
				{
					break;
				}
			}
			o_line=line;
			return true;
		}
		else
		{
			return false;
		}
	}

	MLINLINE void file::write_line(const char* i_line) const
	{
		fputs(i_line,m_handle);
		fputs("\n",m_handle);
	}

	MLINLINE unsigned file::read_bytes(char* o_bytes, unsigned i_numbytes) const
	{
		return (unsigned)fread(o_bytes,1,i_numbytes,m_handle);
	}

	MLINLINE void file::write_bytes(const char* i_bytes, unsigned i_numbytes) const
	{
		fwrite(i_bytes,1,i_numbytes,m_handle);
	}

	MLINLINE bool file::opened() const
	{
		return m_handle!=NULL;
	}

	MLINLINE unsigned file::size() const
	{
		return m_size;
	}

	MLINLINE 	ctr::string get_extension(const char* i_filename)
	{
		const char* tmp=i_filename;

		while (tmp)
		{
			if (*tmp==".")
				break;

			++tmp;
		}

		getto
	}

}

#endif//_file_h_