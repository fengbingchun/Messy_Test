import sys
import yaml

# Blog: https://blog.csdn.net/fengbingchun/article/details/88090609

def main():
	print("#### test start ####")
	f = open("config.yml")
	content = yaml.load(f)
	print(content)
	print("#### test end ####")

if __name__ == "__main__":
	main()

