import shutil,os

def generate_file(file,old_str,new_str):
    file_data = ''
    with open(file, "r", encoding="utf-8") as f:
        for line in f:
            if old_str in line:
                line = line.replace(old_str,new_str)
            file_data += line
    with open(file,"w",encoding="utf-8") as f:
        f.write(file_data)

if __name__ == "__main__":

    language = input("选择语言：\n【1】rclcpp-executor\n【2】rclcpp-componet\n【3】rclpy-executor\n")
    if language == '1':

        package = input("输入包名，用于创建新包:")
        small = input("输入小写变量名,用于yaml变量前缀与文件名称:")
        big = input("输入首字母大写变量名,用于Class Name声明:")
        shutil.copytree("rclcpp-executor-template", package)
        shutil.copytree(package+"/include/template", package+"/include/"+package)
        shutil.rmtree(package+"/include/template")

        #rename
        shutil.move(package+"/config/template.yaml",package+"/config/"+small+".yaml")
        shutil.move(package+"/include/"+package+"/template.hpp",package+"/include/"+package+"/"+small+".hpp")
        shutil.move(package+"/include/"+package+"/template_handle.hpp",package+"/include/"+package+"/"+small+"_handle.hpp")
        shutil.move(package+"/launch/template.launch",package+"/launch/"+small+".launch")
        shutil.move(package+"/launch/template.launch.py",package+"/launch/"+small+".launch.py")
        shutil.move(package+"/src/template.cpp",package+"/src/"+small+".cpp")
        shutil.move(package+"/src/template_handle.cpp",package+"/src/"+small+"_handle.cpp")

        #small
        generate_file(package+"/include/"+package+"/"+small+".hpp",'template',small)
        generate_file(package+"/include/"+package+"/"+small+"_handle.hpp",'template',small)
        generate_file(package+"/src/"+small+"_handle.cpp",'template',small)
        generate_file(package+"/src/"+small+".cpp",'template',small)
        generate_file(package+"/src/"+"main.cpp",'template',small)
        generate_file(package+"/CMakeLists.txt",'template',small)
        generate_file(package+"/package.xml",'template',small)
        generate_file(package+"/launch/"+small+".launch",'template',small)
        generate_file(package+"/launch/"+small+".launch.py",'template',small)
        generate_file(package+"/config/"+small+".yaml",'template',small)

        #big
        generate_file(package+"/include/"+package+"/"+small+".hpp",'Template',big)
        generate_file(package+"/include/"+package+"/"+small+"_handle.hpp",'Template',big)
        generate_file(package+"/src/"+small+"_handle.cpp",'Template',big)
        generate_file(package+"/src/"+small+".cpp",'Template',big)
        generate_file(package+"/src/"+"main.cpp",'Template',big)
        generate_file(package+"/launch/"+small+".launch",'Template',big)
        generate_file(package+"/launch/"+small+".launch.py",'Template',big)

        #upper
        generate_file(package+"/include/"+package+"/"+small+"_handle.hpp",'TEMPLATE',small.upper())
        generate_file(package+"/include/"+package+"/"+small+".hpp",'TEMPLATE',small.upper())

    
