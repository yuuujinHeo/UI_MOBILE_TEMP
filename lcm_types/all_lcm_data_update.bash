
rm *.hpp

find ./ -name '*.lcm' -exec basename {} \; > all_lcm_file_list.txt
    
cat all_lcm_file_list.txt | while read line
do
    echo $line
    lcm-gen -x $line
done



find ./ -name '*.hpp' -exec basename {} \; > all_hpp_file_list.txt

cat /dev/null > lcm_rb.h

cat all_hpp_file_list.txt | while read line
do
    echo $line
    
#    printf "#include \"lcm_types/lcm_rb/%s\"\n" $line >> lcm_rb.h
    printf "#include \"lcm_rb/%s\"\n" $line >> lcm_rb.h
done
