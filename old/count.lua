local lfs=require("lfs")
local lines=0
for file in lfs.dir("C:\\Users\\Kevin\\Documents\\robotics\\testbot") do
	if file:match("%.c$") then
		local fl=io.open(file,"r")
		for _ in fl:read("*a"):gmatch("\n") do
			lines=lines+1
		end
		fl:close()
	end
end
print(lines)
