#include "stdafx.h"
#include "ConMySQL.h"
#include <string.h>

ConMySQL::ConMySQL()
{
	mysql_init(&my_SQL_Con);//分配，初始化数据指针
	
	if (!mysql_real_connect(&my_SQL_Con, "localhost", "root", "948926865", "face_detected", 3306, NULL, 0))
	{
		//显示错误信息
	}
	else
	{
		//显示连接成功信息
	}
}

ConMySQL::ConMySQL(char* host_add, char* user, char* pwd, char* database_name, int port)
{
	mysql_init(&my_SQL_Con);
	if (!mysql_real_connect(&my_SQL_Con, host_add, user, pwd, database_name, port, NULL, 0))
	{
		//显示错误信息
	}
	else
	{
		//显示连接成功信息
	}
}

ConMySQL::~ConMySQL()
{
	mysql_close(&my_SQL_Con);//断开连接
}

bool ConMySQL::chCon(char* host_add, char* user, char* pwd, char* database_name, int port)
{

	if (!mysql_real_connect(&my_SQL_Con, host_add, user, pwd, database_name, port, NULL, 0))
	{
		//显示错误信息
		return false;
	}
	else
	{
		//显示连接成功信息
		return true;
	}
}


bool ConMySQL::get_Stu_Info(stu_info &stuInfo, int num)
{//根据编号查找学生信息
	mysql_query(&my_SQL_Con, "SET NAMES GBK;");
	string sql = format("select * from stu_info where num=%d", num);
//	string sql = "select * from stu_info;";
	int real = mysql_query(&my_SQL_Con, sql.c_str());
//	int real = mysql_real_query(&my_SQL_Con, sql.c_str(), 0);
	if (!real)//为0代表获取的数据不为空
	{
		result = mysql_store_result(&my_SQL_Con);
		int rownum = mysql_num_rows(result);
		if (result)//获取的数据不为空
		{
			row = mysql_fetch_row(result);
			while (row != NULL)//获取具体数据
			{
				stuInfo.num = atoi(row[0]);
				stuInfo.name = row[1];
				stuInfo.id = row[2];
				stuInfo.sex = row[3];
				stuInfo.specialty = row[4];
				stuInfo.classname = row[5];
				row = mysql_fetch_row(result);
			}
			return true;
		}
	}
	return false;
}


int ConMySQL::get_all_Info(stu_info stuInfo[])
{
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	string sql = "select * from stu_info;";
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)//为0代表获取的数据不为空
	{
		result = mysql_store_result(&my_SQL_Con);
		if (result)//获取的数据不为空
		{
			int rowcount = mysql_num_rows(result);
			int i = 0;
			row = mysql_fetch_row(result);
			while (row != NULL)//获取具体数据
			{
				stuInfo[i].num = atoi(row[0]);
				stuInfo[i].name = row[1];
				stuInfo[i].id = row[2];
				if (atoi(row[3]))
					stuInfo[i].sex = true;
				else
					stuInfo[i].sex = false;
				stuInfo[i].specialty = row[4];
				stuInfo[i].classname = row[5];
				string path[4];
				get_Pic_path(stuInfo[i], path[0],path[1],path[2],path[3]);
				for (int j = 0; j < 4; ++j)
					stuInfo[i].path[j] = path[j];
				row = mysql_fetch_row(result);
				++i;
			}
			return rowcount;
		}
	}
	return -1;
}


bool ConMySQL::insert_Stu_Info_full(stu_info stuInfo)
{//全部插入
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	bool result = insert_Stu_Info(stuInfo.id.c_str(), stuInfo.name.c_str(), stuInfo.sex, stuInfo.specialty.c_str(), stuInfo.classname.c_str());
	if (result)
	{
		const char* path[4];
		for (int i = 0; i < 4; ++i)
			path[i] = stuInfo.path[i].c_str();
	
		result = insert_Stu_Pic(stuInfo.num, path[0],path[1],path[2],path[3]);
	}
	return result;
}

bool ConMySQL::insert_Stu_Pic(int num,const char *path1,const char* path2,const char* path3,const char* path4)
{//插入图片路径地址
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	String sql = format("insert into stu_photo (picture1,picture2,picture3,picture4) values ('%s','%s','%s','%s');", path1, path2, path3, path4);
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)
	{
		return true;
	}
	return false;
}


bool ConMySQL::insert_Stu_Info(const char* id, const char* name, bool sex, const char* specialty, const char* classname)
{//插入学生的基本信息
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	int i;
	if (sex) i = 1;
	else i = 0;
	String str = format("insert into stu_info (name,id,sex,specilty,classname) values ('%s','%s',%d,'%s','%s');", name, id, i, specialty, classname);
	int real = mysql_query(&my_SQL_Con, str.c_str());
	if (!real)
	{
		return true;
	}
	return false;
}




bool ConMySQL::get_Pic_path(stu_info stuInfo, string &path1, string &path2, string &path3, string &path4)
{//获取学生的图片信息
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	String sql = format("select * from stu_photo where num=%d;", stuInfo.num);
	
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)//获取的数据不为空
	{
		result2 = mysql_store_result(&my_SQL_Con);
		if (result2)//获取具体数据
		{
			row = mysql_fetch_row(result2);
			path1 = row[1];
			path2 = row[2];
			path3 = row[3];
			path4 = row[4];
		}
		return true;
	}
	return false;
}

/*
bool ConMySQL::update_Reco_Data(string &path, int height, int width)
{//更新识别库的信息

	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	string sql = "select * from cascade;";
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)
	{
		sql = format("update cascade set path = '%s', height = '%d', width = '%d';", path, height, width);
		real = mysql_query(&my_SQL_Con, sql.c_str());
		if (!real)
		{
			return true;
		}
	}
	else
	{
		const char* path_c = path.c_str();
		sql = format("insert into cascade (path,height,width) values ('%s',%d,%d);", path_c, height, width);
		real = mysql_query(&my_SQL_Con, sql.c_str());
		if (!real)
		{
			return true;
		}
	}
	return false;
}


string ConMySQL::get_Reco_Data()
{//获取识别信息的位置
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	string sql = "select path from cascade";
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)
	{
		result = mysql_store_result(&my_SQL_Con);
		if (row = mysql_fetch_row(result))
		{
			path = row[0];
			return path;
		}
	}
}


CvSize ConMySQL::get_Reco_Data_Size()
{//获取图片的标准尺寸
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	string sql = "select * from cascade";
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (real)
	{
		result = mysql_store_result(&my_SQL_Con);
		if (result)
		{
			row = mysql_fetch_row(result);
			CvSize size;
			size.height = atoi(row[1]);
			size.width = atoi(row[2]);
			return size;
		}
	}
}
*/

string ConMySQL::ch_CStringToString(CString s)
{
	USES_CONVERSION;
	std::string str(W2A(s));
	return str;
}


int ConMySQL::update_present_time()
{
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	String sql = format("select * from represent_times");
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)
	{
		result = mysql_store_result(&my_SQL_Con);
		if (result)
		{
			int fieldcount = mysql_num_fields(result);
			sql = format("alter table represent_times add time%d INT(4) DEFAULT 0", fieldcount);
			real = mysql_query(&my_SQL_Con, sql.c_str());
			return fieldcount;
		}
	}
	return false;
}

bool ConMySQL::get_present_time_data(string &present_data)
{
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	String sql = format("select * from represent_times");
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)//获取的数据不为空
	{
		result2 = mysql_store_result(&my_SQL_Con);
		if (result2)//获取具体数据
		{
			int rowcount = mysql_num_rows(result2);
			present_data = "";
			stu_info stu;
			int num = 1;
			row2 = mysql_fetch_row(result2);
			while (row2 != NULL)
			{
				get_Stu_Info(stu, num++);
				present_data.append(format("id:%s  name:%s  ", stu.id.c_str(), stu.name.c_str()));
				for (int i = 1; i < mysql_num_fields(result2); ++i)
				{
					present_data.append(format("time%d: ",i));
					int temp = atoi(row2[i]);
					present_data.append(format("%i   ",temp));
				}
				present_data.append("\n");
				row2 = mysql_fetch_row(result2);
			}
		}
		return true;
	}
	return false;
}


bool ConMySQL::ch_present_time(int num)
{
	mysql_query(&my_SQL_Con, "SET NAMES GBK");
	string sql = format("select * from represent_times where num=%d",num);
	int real = mysql_query(&my_SQL_Con, sql.c_str());
	if (!real)//获取的数据不为空
	{
		result = mysql_store_result(&my_SQL_Con);
		int fieldcount = mysql_num_fields(result);
		if (mysql_num_rows(result))//是否有数据
		{//有数据就选择更新数据库信息
			sql = format("update represent_times set time%d='1' where num=%d", fieldcount-1, num);
			real = mysql_query(&my_SQL_Con, sql.c_str());
			return real;
		}
		else//无数据就选择插入新行,其中，最新一次的签到显示为1，其他显示为0
		{
			sql = format("select * from represent_times");
			real = mysql_query(&my_SQL_Con, sql.c_str());
			if (!real)
			{
				result = mysql_store_result(&my_SQL_Con);
				sql = "insert into represent_times (";
				string sql2 = ") values (";
				int i;
				for (i = 1; i < fieldcount - 1; ++i)
				{
					if (i == 1)
					{
						sql.append(format("time%d", i));
						sql2.append("'0'");
					}
					else
					{
						sql.append(format(",time%d", i));
						sql2.append(",'0'");
					}
				}
				if (i != 1)
				{
					sql.append(format(",time%d", fieldcount - 1));
					sql2.append(",'1'");
				}
				else
				{
					sql.append(format("time%d", fieldcount - 1));
					sql2.append("'1'");
				}
				sql2.append(")");
				sql = sql + sql2;
				real = mysql_query(&my_SQL_Con, sql.c_str());
				return real;
			}
		}

	}

}