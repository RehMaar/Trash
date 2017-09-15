set serveroutput on format truncated
declare
   w_table     VARCHAR2(10) := 'Н_ЛЮДИ';

   col_no             VARCHAR2(10) := 'No.';
   col_name           VARCHAR2(20) := 'Имя столбца';
   col_attr           VARCHAR2(20) := 'Аттрибуты';
   col_type_len_str   VARCHAR2(20) := '';  -- Fill if the type has length.
   null_str           VARCHAR2(100) := ''; -- Fill i the type if NOT NULL.

   prev_col_no       NUMBER    := 0;  -- Previous value of ID.
   col_no_len        NUMBER    := 4;  -- Length of column <No.>.
   col_name_len      NUMBER    := 11; -- Length of column <Name>.
   col_attr_len      NUMBER    := 20; -- Length of column <Attribute>.
   col_attr_name_len NUMBER    := 7;  -- Length of attribute type.


   cursor describe_table is
       select t.column_id        as col_id,
              t.column_name      as col_name,
              t.data_type        as col_type,
              t.data_precision   as col_type_prec,
              t.char_length      as col_type_len,
              t.nullable         as col_null,
              c.comments         as col_comm,
              l.constraint_name  as col_constr_name,
              a.constraint_type  as col_constr_type,
              a.search_condition as col_constr_cond
         from all_tab_columns t 
         join all_col_comments c 
               on c.table_name = t.table_name 
                  and 
                  c.column_name = t.column_name
         join all_cons_columns l
               on t.table_name = l.table_name 
                  and 
                  t.column_name = l.column_name
         join all_constraints  a 
               on l.table_name = a.table_name 
                  and 
                  a.constraint_name = l.constraint_name
            where t.table_name = w_table;
begin
   -- Print header.
   dbms_output.put_line('Таблица: ' || w_table);
   dbms_output.put_line('');
   dbms_output.put_line('');

   dbms_output.put_line(col_no || '  ' || col_name || '   ' || col_attr);  
   dbms_output.put_line(rpad('-', col_no_len,   '-') || ' ' ||
                        rpad('-', col_name_len, '-') || ' ' ||
                        rpad('-', col_attr_len, '-') || ' '
                        );

   for table_row in describe_table
   loop
      -- Check if it is the same ID.
      if prev_col_no = table_row.col_id
      then
         goto print_constraints;
      end if;

      -- Construct column type: NOT NULL.
      if table_row.col_null = 'N'
      then
         null_str := 'NOT NULL';
      elsif table_row.col_null = 'Y'
      then
         null_str := '';
      end if;

      -- Construct column type: data type length.
      if  table_row.col_type_len > 0
      then
         -- For strings.
         col_type_len_str := '(' || table_row.col_type_len || ')';
      elsif table_row.col_type_prec is not null
      then
         -- For numbers.
         col_type_len_str :=  '(' || table_row.col_type_prec || ')';
      else
         col_type_len_str := '';
      end if;

      -- Print <No.> <Column Name> <Attributes: Type>.
      dbms_output.put_line(
         rpad(table_row.col_id,   col_no_len,        ' ') || ' '  ||
         rpad(table_row.col_name, col_name_len,      ' ') || ' '  ||
         rpad('Type',             col_attr_name_len, ' ') || ': ' ||
         table_row.col_type || col_type_len_str || ' ' || null_str
      );
      -- Print <Attributes: Comment> if it exists. 
      if table_row.col_comm is not NULL 
      then
         dbms_output.put_line(
               rpad(' ',       col_no_len + col_name_len + 2, ' ') ||
               rpad('Comment', col_attr_name_len,             ' ') ||
               ': "' || table_row.col_comm || '"'
         );
      end if;

<<print_constraints>>
      -- Print <Attributes: Constr> if it exists and it isn't NOT NULL constr.
      if table_row.col_constr_type = 'C'
            and 
         table_row.col_constr_cond not like '%NOT NULL%'
      then
         dbms_output.put_line(
               rpad(' ',       col_no_len + col_name_len + 2, ' ') ||
               rpad('Constr', col_attr_name_len,             ' ') ||
               ': "' || table_row.col_constr_name || ' CHECK (' ||
               table_row.col_constr_cond || ')"'
         );
      end if;
      -- Save value of current ID.
      prev_col_no := table_row.col_id;
   end loop;
end;
/
