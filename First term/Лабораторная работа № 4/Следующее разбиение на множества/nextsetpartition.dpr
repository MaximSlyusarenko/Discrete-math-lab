Program p;

Uses Sysutils, Math;

Var i, j, r, code, q, g1, h1, g, h, maxi, tmp, f, mini, d: integer; n, k: int64;
a: array[0..5, 0..5] of int64;
kol: array[0..5] of int64;
s, s1: string;
flag: boolean;

begin
	reset (input, 'nextsetpartition.in');
	rewrite (output, 'nextsetpartition.out');
	readln(n, k);
	i := 0;
	while (n <> 0) and (k <> 0) do
	begin
		j := 0;
		readln(s);
		r := 1;
		while (r <= length(s)) do
		begin
			q := r;
			while (s[q] <> ' ') and (q <= length(s)) do
				inc(q);
			s1 := copy(s, r, q - r);
			val(s1, a[i][j], code);
			inc(j);	 
			r := q + 1;
		end;
		//for r := 0 to j - 1 do
		//	write(a[i][r], ' ');
		//writeln;
		kol[i] := j;
		inc (i);
		if (i = k) then
		begin
			q := i;
			maxi := -1;
			//flag := true;
			//while (q > 0) and (flag) do
			//begin
			//	maxi := max(maxi, a[q][kol[q]]);
			//	dec(q);
			//	fl := false;
			//	for g := kol[q] downto 0 do
			//	begin
			//		if (a[q][g] < maxi) then
			//		begin
			//			r := a[q][g];
			//			d := g;
			//			b := q;
			//			fl := true;
			//			break;
			//		end;
			//	end;
			//	if (fl) then
			//	begin
			//		mini := 1000000;
			//		inc(q);
			//		for i := q to k do
			//			for k := 0 to kol[i] do
			//				if (a[i][k] > r) and (a[i][k] < mini) then
			//				begin
			//					mini := a[i][k];
			//					f := i;
			//					e := k;
			//				end;
			//		swap(a[f][e], a[b][d]);
			//		fl := true;
			//		for i := f to d - 1 do
			//			if (a[i][0]	> a[i + 1][0]) then
			//				fl := false;
			//		if (not fl) then
			//		begin
			//			swap(a[f][e], a[b][d]);
			//			dec(q);
			//		end
			//		else
			//		begin
			//			flag := false;
			//			//вывод
			  //
				//	end;	
				//end;
			for  q := k - 1 downto 0 do
			begin
				g1 := -1;
				h1 := -1;
				//for r := kol[q] - 1 downto 0 do
				//begin
				if (a[q][0] < maxi) then
				begin
					for r := 0 to kol[q] - 1 do
						if (a[q][r] < maxi) then
						begin
							g1 := q;
							h1 := r;
						end;
					break;
				end;
				if (a[q][kol[q] - 1] > maxi) then                                                                                                          
				begin
					maxi := a[q][kol[q] - 1];
					continue;
				end;
				//if (a[q][r] < maxi) then
				//begin
				//	g1 := q;
				//	h1 := r;
				//	break;
				//end;
			end;
			mini := 1000000;
			d := g1;
			for q := d + 1 to k - 1 do
				for r := 0 to kol[q] - 1 do
					if (a[q][r] < mini) and (a[q][r] > a[g1][h1]) then
					begin
						mini := a[q][r];	
						g := q;
						h := r;
					end;
			if (g1 = -1) then
			begin
				writeln(n, ' ', n);
				for i := 1 to n do
					writeln(i);
			end;
			if (kol[g1] = 1) then
			begin
				dec(k);
				writeln(n, ' ', k);
				a[g1][h1 + 1] := a[g][h];
				dec(kol[g]);
				for f := 0 to k - 1 do
				begin
					for r := 0 to kol[f] - 1 do
						write(a[f][r], ' ');
					writeln;
				end;
				break;
			end;
			tmp := a[g][h];
			a[g][h] := a[g1][h1];
			a[g1][h1] := tmp;
			writeln(n, ' ', k);
			for f := 0 to k - 1 do
			begin
				for r := 0 to kol[f] - 1 do
					write(a[f][r], ' ');
				writeln;
			end;
			writeln;										
			i := 0;
			readln;
			readln(n, k);
		end;
	end;
end.					