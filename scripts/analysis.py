import os

def count_lines(directory, extensions):
    total_lines = 0
    exclude_list = ['build', 'cmake-build-debug','output','node_modules']
    for root, dirs, files in os.walk(directory):
        # 排除构建目录
        for ex_dir in exclude_list:
            if ex_dir in dirs:
                dirs.remove(ex_dir)

        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                        total_lines += sum(1 for _ in f)
                except:
                    continue

    return total_lines

# 配置要统计的文件类型
extensions = ['.cpp', '.h','.json','.html','.js','.py']
lines = count_lines('..\\', extensions)
print(f"总代码行数: {lines}")