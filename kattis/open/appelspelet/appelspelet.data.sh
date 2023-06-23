a=(alf beata);read n;echo ${a[$((((n%340)&35)=~ ^(1|33|35)$?0:1))]}
