# i f n d e f   _ _ M S G _ D E F I N E _ _  
 # d e f i n e   _ _ M S G _ D E F I N E _ _  
 # i n c l u d e   < s t r i n g >  
 u s i n g   n a m e s p a c e   s t d ;  
 / * * * *  
 1 0 0 0 0 ~ 1 9 9 9 9 :S��:N  J A V A T�S��x 
 2 0 0 0 0 ~ 2 9 9 9 9 :S��:NT�S��x 
 3 0 0 0 0 ~ 3 9 9 9 9 :S��:N�{�l��x 
 4 0 0 0 0 ~ 4 9 9 9 9 :S��:N�[7b�z��x 
 5 0 0 0 0 ~ 5 9 9 9 9 :S��:N�y�R�z��x 
 6 0 0 0 0 ~ 6 9 9 9 9 :S��:NAm�ZSO�mo`x 
  
 3 3 5 0 0 0R3 3 5 9 9 :Nb_SO���Nx�k� 
 * * * * * /  
 e n u m   _ J s o n M s g T y p e / / �Sߍ*�T*N!jWWZPNT�v�mo`�k 
 {  
 	 J S O N M S G T Y P E _ N O T I F Y   =   0 , / / ��w�mo`( ����Bl�eN ����VY)  
 	 J S O N M S G T Y P E _ R E Q U E S T   =   1 , / / ��Bl�mo`( ����Bl�e ����VY)  
 	 J S O N M S G T Y P E _ R E S P O N S E   =   2 , / / �VY�mo` 
 } ;  
  
 # i f n d e f   _ _ A L A R M _ M S G _ D E A L _ S T A T E _ _  
 # d e f i n e   _ _ A L A R M _ M S G _ D E A L _ S T A T E _ _  
 e n u m   _ A l a r m M s g D e a l S t a t e  
 {  
 	 U N _ D E A L ,  
 	 T R A C I N G ,  
 	 E N D _ T R A C E ,  
 	 F A L S E _ A L A R M ,  
 	 L O S T _ T A R G E T , 	 / / "N1Y�vh�S_MR�Nir؏(W�v:g�FO/f�l	g;uFh 
 } ;  
 # e n d i f  
  
 / *  
 *   0 �ck8^ 
 *   4 0 0 0 - 4 3 9 9 	 �[7b�zN�R �Bl�Sx�k 
 *   4 4 0 0 - 4 9 9 9 	 �[7b�zN�Rf�JT�Sx�k 
 *   4 0 0 0 0 - 4 0 9 9 9 	 ��Yu�Sx�k 
 *   4 1 0 0 0 - 4 4 9 9 9 	 Y��S�~�[7b�z�v�Sx�k 
 *   4 5 0 0 0 - 4 9 9 9 9 	 �[7b�z���Sx�k 
 * /  
  
 e n u m   _ C h a n g e M e d i a C a m e r a  
 {  
 	 C H A N G E _ M E D I A _ C A M E R A _ T Y P E _ A D D   = 0 ,   / / �m�R�v:g   
 	 C H A N G E _ M E D I A _ C A M E R A _ T Y P E _ D E L E T E   =   1 ,   / /  Rd��v:g 
 	 C H A N G E _ M E D I A _ C A M E R A _ T Y P E _ R E V I S E   =   2 ,   / / �O9e�v:g 
         C H A N G E _ M E D I A _ C A M E R A _ T Y P E _ I N I   =   3 ,   / / R�YS�m�R�v:g 
 } ;  
 e n u m   _ C h a n g e M e d i a C a m e r a E r r T y p e  
 {  
 	 C A M E R A _ N O N E X I S T E N T = 1 ,   / / �v:gNX[(W 
         C O N N E C T _ T I M E O U T   = 2 ,   / / ���c���e 
 	 P A S S W O R D _ E R R   =   3 ,   / / �[x�� 
 } ;  
  
  
 e n u m   _ J s o n M s g R t s p S e r v e r  
 {  
 	 J S O N M S G C O D E _ R T S P S E R V E R _ O K   =   0 ,  
 	 J S O N M S G C O D E _ M E D I A _ C H A N G E _ C A M E R A _ S U C C E S S   =   0 ,  
 	 J S O N M S G C O D E _ R T S P _ C O N N E C T _ R E Q _ R E P L Y   =   6 0 0 0 0 , / / r t s p ޏ�c��Bl�VY 
 	 J S O N M S G C O D E _ R T S P _ C A M E R A _ S T A T U S _ R E P L Y   =   6 0 0 0 1 , / / c a m e r a   s t a t u s   r e p l y  
 	 J S O N M S G C O D E _ R T S P _ A L A R M _ V I D E O _ S A V E   =   6 0 0 0 2 ,  
 	  
 	 J S O N M S G C O D E _ M E D I A _ C H A N G E _ C A M E R A _ E R R   =   6 5 0 0 1 ,  
 } ;  
 e n u m   _ J s o n M s g C o d e S e n d / / �S�~Y萄vN�R��Bl 
 {  
 	 J S O N M S G C O D E _ C L I E N T _ O K   =   0 ,  
 	 J S O N M S G C O D E _ C L I E N T _ C O N N E C T T E S T   =   4 0 0 0 , 	 / / �[7b�zޏ�cg�RhV  KmՋ  ��Bl 
 	 J S O N M S G C O D E _ C L I E N T _ L O G I N   =   4 0 0 1 , 	 / / �[7b�z{vU_N�R��Bl 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ T R E E I N F O   =   4 0 0 2 , 	 / / �[7b�z{vU_b�R����S�v:gRh��Oo`N�R��Bl 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ W A R N C A M I N F O   =   4 0 0 3 , 	 / / ���S�bf��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ Q U I T   =   4 0 0 4 , 	 / / �[7b�z ��Q��BlN�R 
 	 J S O N M S G C O D E _ C L I E N T _ A C C O U N T Q U I T   =   4 0 0 5 , 	 / / �[7b�zS_MR&�7b ��Q��BlN�R 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ M A P S I N F O   =   4 0 0 6 , 	 / / �[7b�z��Bl0W�V�Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ A L A R M _ D E A L   =   4 0 0 7 , 	 / / �[7b�zYt�bf��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ T R A C E _ P E R S O N _ C H A N G E   = 4 0 0 8 , 	 / / �[7b�zRbc0Rߍ*�h~{u�c�[ߍ*��g*N�bf�I D  
 	 J S O N M S G C O D E _ C L I E N T _ T R A C E _ P E R S O N _ T E R M I N E R   =   4 0 0 9 , 	 / / �[7b�z�~_g��*��g*N�bf�I D  
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ L O O K _ B A C K   =   4 0 1 0 , 	 / / �[7b�z  �g⋥bf��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ S E C N D _ R G N S   =   4 0 1 1 , 	 / / �[7b�z��Q�Yt  �g⋥bf��Oo`  ���S\:S�WRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ C A M R _ L I S T   =   4 0 1 2 , 	 / / �[7b�z��Q�Yt  �g⋥bf��Oo`  ���S�v:gRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ D E T A I L   =   4 0 1 3 , 	 / / �[7b�z  �g�US*N�bf��Nir�v�bf���~�Oo`( �NT�S���S�bf�Ɖ��Rh�)  
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ V I S E O   =   4 0 1 4 , 	 / / �[7b�z��Q�Yt  z��^/ ��:g�d>e�bf�Ɖ�� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ T R A C K E R   =   4 0 1 5 , 	 / / �[7b�z��Q�Yt  >f:y�bf�h��� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ L O O K _ B A C K   =   4 0 1 6 , 	 / / �[7b�z  �g⋓b�b�V 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ S E C N D _ R G N S   =   4 0 1 7 , 	 / / �[7b�z��Q�Yt  �g⋓b�b�V�Oo`  ���S\:S�WRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ C A M R _ L I S T   =   4 0 1 8 , 	 / / �[7b�z��Q�Yt  �g⋓b�b�V�Oo`  ���S�v:gRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ L O O K _ P R E V   =   4 0 1 9 , 	 / / �[7b�z�Q�Yt  �g⋓b�b�V
N Nu� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ L O O K _ N E X T   =   4 0 2 0 , 	 / / �[7b�z�Q�Yt  �g⋓b�b�VN Nu� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ R E C O R D _ L O O K _ B A C K   =   4 0 2 1 , 	 / / �[7b�z  �g��d\O�e�_ 
 	 J S O N M S G C O D E _ C L I E N T _ A C C O U N T _ C H A N G E _ P A S S W O R D   =   4 0 3 0 , 	 / / �[7b�z�O9e�[x 
 	 J S O N M S G C O D E _ C L I E N T _ L O G _ R E C O R D   =   4 0 3 1 , 	 / / �[7b�z
N O�e�_�Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N   =   4 0 4 1 , / / �[7b�z��Bl���{$N _�N8��v�v<O�^�1 V S 1 	� 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N _ B A C K   =   4 4 4 1 , / / �[7b�z��Bl���{$N _�N8��v�v<O�^ԏ�V�1 V S 1 	�    / / / J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N _ R E P L Y 9eJ S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N _ B A C K  
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ U S I N G _ I M G _ C H E C K I N _ I M G   =   4 0 4 2 , / /  
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ U S I N G _ I M G _ C H E C K I N _ I M G _ B A C K   =   4 4 4 2 , / /  
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N _ N     =       4 0 4 3 ,   / / 1 v s n 	 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ 1 V S N 9eJ S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N _ N  
 	  
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ C H E C K I N _ N _ B A C K   =   4 4 4 3 ,       / / 1 v n �[�k�V�� 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ L I B S   =   4 0 4 4 ,       / / ���S�^Rh� 
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ F A C E _ L I B S _ B A C K   =   4 4 4 4 ,       / / ���S�^Rh��V�� 
 	 A n a l y z e M o d e l _ S U R C H _ I M G 1 _ L O A D   =   1 6 1 0 ,   / / 1 v 1 �V�P1 �R}� 
 	 A n a l y z e M o d e l _ S U R C H _ I M G 2 _ L O A D   =   1 6 1 1 ,   / / 1 v 1 �V�P2 �R}� 
 	 A n a l y z e M o d e l _ S U R C H _ I M G 1 _ U P _ L O A D I N G   =   1 6 1 2 ,   / / �V�P1 
N O 
 	 A n a l y z e M o d e l _ S U R C H _ I M G 2 _ U P _ L O A D I N G   =   1 6 1 3 ,   / / �V�P2 
N O 
 	 A n a l y z e M o d e l _ S U R C H _ R E S I M G _ G E T   =   1 6 1 4 ,   / / �gw�~�g�V�P 
 } ;  
 e n u m   _ S e r v e r R e q u e s t C o d e / / S e r v e r �S�~Y萄vN�R��Bl 
 {  
 	 J S O N M S G C O D E _ S E R V E R _ G E T I N F O _ O K   =   0 , / / ��Blb�R 
 	 J S O N M S G C O D E _ S E R V E R _ G E T C A M E R A _ I N F O   =   2 0 0 0 0 , / / g�RhVTj a v a ��Bl�v:gh�Oo` 
 	 J S O N M S G C O D E _ S E R V E R _ G E T C A M E R A _ N U M B E R S   =   2 0 0 0 1 , / / g�RhVTj a v a ��Bl�v:gpeϑ 
 	 J S O N M S G C O D E _ S E R V E R _ G E T _ P C _ C L I E N T _ V E R S I O N   =   2 0 0 0 2 , / / g�RhVTj a v a ��Blp c o��NHr,g 
 	 J S O N M S G C O D E _ S E R V E R _ C O N F I R M _ U S E R N A M E _ A N D _ P W D   =   2 0 0 0 3 , / / g�RhVTj a v a ��Bl����(u7bT�[x 
 	 J S O N M S G C O D E _ S E R V E R _ F A C E R E C G   =   2 0 0 0 4 , / / �N8�Ƌ+R��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ P U S H T O _ R T S P S   =   2 0 0 0 5 , / / �c�r t s p   s e r v e r   �mo` 
 	 J S O N M S G C O D E _ S E R V E R _ F A C E D E T E C T _ C O N N E C T _ R E Q   =   2 0 0 0 6 , / / �N8��hKmޏ�c��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ F A C E T E L L _ C O N N E C T _ R E Q   =   2 0 0 0 7 , / / �N8�Ƌ+Rޏ�c��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ S H A P E _ C O N N E C T _ R E Q   =   2 0 0 0 8 , / / �NL�ޏ�c��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ R T S P _ C O N N E C T _ R E Q   =   2 0 0 0 9 , / / r t s p ޏ�c��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ F E A _ C R E A T E _ S U C C E S S   =   0 , / / f e a ubb�R 
 	 J S O N M S G C O D E _ S E R V E R _ T R A C K _ A L I V E _ C H E C K   =   2 0 0 1 0 , / / ߍ*��~z�_��hKm 
 	 J S O N M S G C O D E _ S E R V E R _ S E A R C H _ C A P T U R E _ L O O K _ B A C K   =   2 0 0 1 1 , / / �b�b�g� 
 	 J S O N M S G C O D E _ S E R V E R _ M O N I T O R _ C A M E R A   =   2 0 0 1 2 , / / Dd�P4Y�v�c  J A V A �z�c6e 
 	 J S O N M S G C O D E _ S E R V E R _ M O N I T O R _ S E R V E R   =   2 0 0 1 3 , / / g�RhV�v�c�J A V A �z�c6e 
 	 J S O N M S G C O D E _ S E R V E R _ M O N I T O R _ N E T W O R K   =   2 0 0 1 4 , / / Q�~Amϑ�v�c    J A V A �z�c6e 
 	 J S O N M S G C O D E _ S E R V E R _ G E T S T R A T E G Y   =   2 0 0 1 5 , / / V{eu    J A V A �z�c6e 
 	 J S O N M S G C O D E _ S E R V E R _ S E A R C H _ A L A R A M _ L O O K _ B A C K   =   2 0 0 1 6 , / / �bf�Rh��g� 
 	 J S O N M S G C O D E _ S E R V E R _ S E A R C H _ R E C O R D _ L O O K _ B A C K   =   2 0 0 1 7 , / / �e�_�g� 
 	 J S O N M S G C O D E _ S E R V E R _ L O G _ R E C O R D   =   2 0 0 1 8 , / / �e�_X[�P 
 	 J S O N M S G C O D E _ S E R V E R _ S E A R C H _ A L A R A M _ D E T A I L   =   2 0 0 1 9 , / / US*N�Nir�bf��v�V>eƉ���T��*�_�g� 
 	 J S O N M S G C O D E _ S E R V E R _ S E N D _ C A M E R A _ S T A T U S _ Q U E R Y   =   2 0 0 2 0 , / / s e r v e r   �S��v:g�r`�g� 
 	 J S O N M S G C O D E _ S E R V E R _ J A V A _ C O N N E C T _ R E Q   =   2 0 0 2 1 , / / j a v a ޏ�c��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ C L U S T E R _ I N F O _ R E Q   =   2 0 0 2 3 , / / c l u s t e r   i n f o   ��Bl	  
 	 J S O N M S G C O D E _ S E R V E R _ G E T _ C H A N G E _ C A M E R A _ R E Q   =   2 0 0 2 2 , / / c h a n g e   c a m e r a   ��Bl 
 	 J S O N M S G C O D E _ S E R V E R _ A L A R M _ V I D E O _ S A V A   =   2 0 0 2 3 , / / a l a r m   v i d e o   s a v e   r e q   	  
 } ;  
 e n u m   _ S e r v e r R e p o n s e C o d e  
 {  
 	 J S O N M S G C O D E _ S E R V E R _ R E S P O N S E _ O K   =   0 ,  
 } ;  
 e n u m   _ J a v a R e p o n s e C o d e  
 {  
 	 J S O N M S G C O D E _ J A V A _ R E P O N S E _ O K   =   0 , / / ԏ�VO K  
 	 J S O N M S G C O D E _ J A V A _ S E N D _ P C _ C L I E N T _ V E R S I O N   =   1 0 0 0 0 , / / j a v a   �VYp c �[7b�zHr,g�Oo` 
 	 J S O N M S G C O D E _ J A V A _ S E N D _ U S E R N A M E _ N O T _ E X I S T   =   1 0 0 0 1 , / / j a v a   �VY(u7bTNX[(W 
 	 J S O N M S G C O D E _ J A V A _ S E N D _ P A S S W O R D _ W R O N G   =   1 0 0 0 2 , / / j a v a   �VY�[x�� 
 	 J S O N M S G C O D E _ J A V A _ S E N D _ C A M E R A _ I N F O   =   1 0 0 0 3 , / / j a v a   ԏ�V�v:g�Oo` 
 	 J S O N M S G C O D E _ J A V A _ S E N D _ I P _ I N F O   =   1 0 0 0 4 , / / j a v a   Ts e r v e r �z�S�i p I{�mo` 
 	 J S O N M S G C O D E _ J A V A _ S E N D _ L O G I N _ C O N F I R M _ O K   =   1 0 0 0 5 , / / j a v a   {vU_����o k  
 	 J S O N M S G C O D E _ J A V A _ S E N D _ C A P _ Q U E R Y _ R E S U L T   =   1 0 0 0 6 , / / j a v a   ԏ�V�b�b�g��~�g 
 	 J S O N M S G C O D E _ J A V A _ M O N I T O R _ C A M E R A   =   1 0 0 0 7 , / / Dd�P4Y�v�c    J A V A �z�S� 
 	 J S O N M S G C O D E _ J A V A _ M O N I T O R _ S E R V E R   =   1 0 0 0 8 , / / g�RhV�v�c    J A V A �z�S� 
 	 J S O N M S G C O D E _ J A V A _ M O N I T O R _ N E T W O R K   =   1 0 0 0 9 , / / Q�~Amϑ�v�c    J A V A �z�S� 
 	 J S O N M S G C O D E _ J A V A _ R E T U R N _ S T R A T E G Y   =   1 0 0 1 0 , / / V{eu  J A V A �z�S� 
 	 J S O N M S G C O D E _ J A V A _ S E A R C H _ A L A R A M _ L O O K _ B A C K   =   1 0 0 1 1 , / / �bf�Rh��g�ԏ�V 
 	 J S O N M S G C O D E _ J A V A _ S E A R C H _ A L A R A M _ D E T A I L   =   1 0 0 1 2 , / / US*N�Nir�bf��v�V>eƉ���T��*�_�g�ԏ�V 
 	 J S O N M S G C O D E _ J A V A _ S E A R C H _ R E C O R D _ L O O K _ B A C K   =   1 0 0 1 3 , / / �e�_�g� 
 	 J S O N M S G C O D E _ J A V A _ L O G _ R E C O R D   =   1 0 0 1 4 , / / �e�_X[�P2  
 / / 	 J S O N M S G C O D E _ S E R V E R _ G E T S T R A T E G Y   =   2 0 0 1 5 , / / V{eu��Bl 
 	 J S O N M S G C O D E _ J A V A _ C H A N G E _ F A C E L I B   =   1 0 0 1 6 , / / J a v a ��Bl�O9e�N8��^�v�N8���Bl 
 	 J S O N M S G C O D E _ J A V A _ C H A N G E _ C A M E R A   =   1 0 0 1 7 , / / c h a n g e   f a c e d e t e c t i o n   c a m e r a   	  
 	 J S O N M S G C O D E _ M E D I A _ C H A N G E _ C A M E R A   =   1 0 0 1 7 , / / m e d i a   c h a n g e   c a m e r a  
 	 J S O N M S G C O D E _ T R A C K _ C H A N G E _ C A M E R A   =   1 0 0 1 7 , / / m e d i a   c h a n g e   c a m e r a  
 	 J S O N M S G C O D E _ J A V A _ S T A R T _ S E R V E R _ I T E M S   =   1 0 0 1 8 , / / j a v a   c o n t r o l   s e r v e r   c o m b i n a t i o n  
 	  
 	 / * C U I J I A N H U A + A D D + C O D E * /  
 	 J S O N M S G C O D E _ J A V A _ C H A N G E _ S T R A T E G Y   =   1 0 0 1 9 ,         / / eg�j a v a �z�v  ^�cV{eu�f9e  �mo` 
 	 J S O N M S G C O D E _ J A V A _ C H A N G E _ S T A T E G   =   1 0 0 2 0 , 	 	 / / �O9eV{eu 
 	 J S O N M S G C O D E _ J A V A _ C H A N G E _ C A M E R A _ S U C C E S S   =   0 ,   / / j a v a   c h a n g e   c a m e r a  
 	  
 } ;  
 e n u m   _ F a c e F u n c R e q u e s t C o d e  
 {  
 	 J S O N M S G C O D E _ R E S P O N S E _ O K   =   0 , / / �{�lԏ�VO K  
 	 J S O N M S G C O D E _ F A C E D E T E C T E D _ M S G   =   3 0 0 0 0   , / / �hKm0R�N8� 
 	 J S O N M S G C O D E _ F A C E _ N E E D _ T E L L   =   3 0 0 0 1 , / / �N8�Ƌ+R��Bl 
 	 J S O N M S G C O D E _ F A C E _ T E L L _ R E S U L T   =   3 0 0 0 2 , / / �N8�Ƌ+R�~�g 
 	 J S O N M S G C O D E _ F A C E _ D E T E C T _ C O N N E C T _ R E P L Y   =   3 0 0 0 3 , / / �N8��hKmޏ�c��Bl�VY 
 	 J S O N M S G C O D E _ F A C E _ T E L L _ C O N N E C T _ R E P L Y   =   3 0 0 0 4 , / / �N8�Ƌ+Rޏ�c��Bl�VY 
 	 J S O N M S G C O D E _ F A C E D E T E C T I O N _ P I C T U R E D I R _ O U T   =   3 0 0 0 5 , / / US _�VGr 
 	 J S O N M S G C O D E _ F A C E D E T E C T I O N _ P I C T U R E D I R _ I N   =   3 0 0 0 6 , / / �VGr�e�N9Y 
 	 J S O N M S G C O D E _ F A C E D E T E C T I O N _ I N I T _ I N   =   3 0 0 0 7 , / / ���{yr�_<P 
 	 J S O N M S G C O D E _ F A C E I D F _ F A C E F E A T U R E S _ O U T   =   3 0 0 0 8 , / / yr�_<P���{�[b 
 	 / / �Nb_R�g�NN�Nb_R�g�N�~z 
 	 J S O N M S G C O D E _ H U M A N S H A P E _ I N I T _ I N   = 3 0 1 0 1 , / / R�YS�c�S 
 	 J S O N M S G C O D E _ H U M A N S H A P E _ I N I T _ O U T   = 3 0 1 0 2 , / / R�YS�~�g�c�S 
 	 J S O N M S G C O D E _ H U M A N S H A P E _ A L A R M _ I N   = 3 0 1 0 3 , / /  OeQJTf��Oo`�c�S 
 	 J S O N M S G C O D E _ H U M A N S H A P E _ A L A R M _ O U T   = 3 0 1 0 4 , / /  O�QJTf��Oo`�[�^�v�Nb_Fh�c�S 
 	 J S O N M S G C O D E _ A L L H U M A N S H A P E _ A L L H U M A N S H A P E _ I N   = 3 0 1 0 5 , / /  OeQ͑Ƌ+R�c�S 
 	 J S O N M S G C O D E _ A L L H U M A N S H A P E _ A L L H U M A N S H A P E _ O U T   = 3 0 1 0 6 ,   / /  O�Q͑Ƌ+R�Oo`�c�S 
 	 / / ߍ*�N�R;���Nߍ*��{�l 
 	 J S O N M S G C O D E _ T A I L A F T E R _ O N E H U M A N S H A P E _ O U T   =   3 0 2 0 1 , / /  OeQJTf��Nb_Fh�g�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ A L L H U M A N S H A P E _ I N   =   3 0 2 0 2 , / /  OeQ ���͑Ƌ+R�Nb_�v�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ A L L H U M A N S H A P E _ O U T   =   3 0 2 0 3 , / /  OeQ͑Ƌ+R�Nb_�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ R E S _ L O S T _ I N   =   3 0 2 0 4 , / /  OeQߍ*��r`�"N1Y	��Oo`�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ R E S _ F O L L O W I N G _ I N   =   3 0 2 0 5 , / /  OeQߍ*��r`�ߍ*�	��Oo`�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ R E S _ S W A P C A M E R A _ I N   =   3 0 2 0 6 , / /  OeQߍ*��r`��Nirp��Q�v:g	��Oo`�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ R E S _ S W A P C A M E R A _ O U T   =   3 0 2 0 7 , / /  O�Qߍ*��r`��Nirp��Q�v:g	��Oo`�c�S 
 	 J S O N M S G C O D E _ T A I L A F T E R _ M I S I N F O R M T I O N _ O U T 	 = 3 0 2 0 8 , / /  O�Qb 
  
 	 / / ߍ*�N�R;���Nj a v a �~z 
 	 J S O N M S G C O D E _ J A V A S E R V E R _ I N I T _ O U T   =   3 0 3 0 1 , / / ��BlR�YSpenc 
 	 J S O N M S G C O D E _ J A V A S E R V E R _ I N I T _ I N   =   3 0 3 0 2 , / / ԏ�VR�YSpenc 
 	 J S O N M S G C O D E _ J A V A S E R V E R _ T R A C K _ O U T   =   3 0 3 0 3 , / / �S�ߍ*�h����c�S 
 	 J S O N M S G C O D E _ J A V A S E R V E R _ F O L L O W _ O U T   =   3 0 3 0 4 , / / �S�ߍ*��c�S 
 	 J S O N M S G C O D E _ J A V A S E R V E R _ L O S T _ O U T   =   3 0 3 0 5 , / / �S�"N1Y�c�S 
 	  
 	 J S O N M S G C O D E _ T A I L A F T E R _ F R A M _ O U T   = 3 0 4 0 1 , / / ߍ*� 
 	 J S O N M S G C O D E _ T A I L A F T E R _ C H A N G E C A M E R A _ O U T   = 3 0 4 0 2 , / / Rbc�v:g 
 	 / / N�[7b�z�~z�v�mo` 
 	 J S O N M S G C O D E _ C L I E N T _ T R A C K   =   3 0 6 0 1 , / / ߍ*� 
 	 J S O N M S G C O D E _ C L I E N T _ W R O N G   =   3 0 6 0 2 , / / b 
  
 	 J S O N M S G C O D E _ H U M A N S H A P E _ O N E H U M A N S H A P E _ I N   =   3 0 5 0 1 , / /  OeQ�Nb_Fh�g�c�S 
 	 J S O N M S G C O D E _ H U M A N S H A P E _ A L L H U M A N S H A P E _ O U T   =   3 0 5 0 2 , / /  O�Q ���ZP͑Ƌ+R�Nb_�v�c�S 
 	 J S O N M S G C O D E _ H U M A N S H A P E _ A L L H U M A N S H A P E _ I N   =   3 0 5 0 3 , / /  OeQ͑Ƌ+R�Nb_�c�S 
 	 / / J S O N M S G C O D E _ T A I L A F T E R _ A L L H U M A N S H A P E _ O U T   =   3 0 5 0 2 , / /  O�Q ���ZP͑Ƌ+R�Nb_�v�c�S 
 	 / / J S O N M S G C O D E _ T A I L A F T E R _ A L L H U M A N S H A P E _ I N   =   3 0 5 0 3 , / /  OeQ͑Ƌ+R�Nb_�c�S 
  
  
  
 	 / / �[7b�z��Blߍ*��Nir��~�Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ P A G A C H A N G E _ G E T _ T R A C K _ D E T A I L   =   3 0 6 0 3 , / / ߍ*� 
 	 J S O N M S G C O D E _ T R A C K D O _ C L I E N T _ A L A R M _ D E A L   =   3 0 6 0 4 , / / �bf��mo`Yt��Bl  ߍ*�bb 
 	  
 	 J S O N M S G C O D E _ S E R V E R _ F A C E _ D E T E C T _ C H A N G E _ C A M E R A _ E R R   =   3 1 5 0 0 3 , / / 9e�S�v:g�� 
 	 J S O N M S G C O D E _ S E R V E R _ F A C E _ D E T E C T _ C H A N G E _ C A M E R A _ S U C C E S S   =   0 , / / 9e�S�v:gO K  
  
 	 J S O N M S G C O D E _ F A C E D T _ G E T _ F A C E _ C H E C K I N _ N O _ R E A D _ P I C   =   3 1 5 0 1 , / / �l	g���S0R�V�P 
 	 J S O N M S G C O D E _ F A C E D T _ G E T _ F A C E _ C H E C K I N _ F A C E _ U N Q U A   =   3 1 5 0 2 , / / �N8�(�ϑNT<h 
 	 J S O N M S G C O D E _ F A C E D T _ N O _ F A C E _ D T   =   3 1 5 0 4 , / / �l	g�hKm0R�N8� 
  
 } ;  
 e n u m   _ J a v a R e q u e s t C o d e  
 {  
  
 } ;  
 e n u m   _ C l u s t e r T y p e   {  
 	 F A C E _ D E T E C T I O N   =   0 , / / �N8��hKm 
 	 F A C E _ T E L L   =   1 , / / �N8�Ƌ+R	  
 	 H U M A N _ S H A P E   =   2 , / / �Nb_ 
 	 R T S P _ S E R V E R   =   3 , / / r t s p  
 	 H U M A N _ T R A C K   =   4 , / / t r a c k  
 	 P I C _ S E A R C H   =   7 , / / p i c   s e a r c h  
 } ;  
 e n u m   _ S e r v e r R e q u e s t R e p l a y  
 {  
 	 J S O N M S G C O D E _ S E R V E R _ G E T I N F O _ F A I L E D   =   - 1 ,  
 } ;  
 e n u m   _ J s o n M s g C o d e G e t / / �c6eY� OeQ�v�mo` 
 {  
 	 J S O N M S G C O D E _ C L I E N T _ S E N D _ T R E E I N F O   =   4 4 0 0 , 	 / / g�RhV�S��v:gRh��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ S E N D _ W A R N C A M I N F O   =   4 4 0 1 , 	 / / g�RhV�S��bf��v:g�Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ S E N D _ T R A C E I N F O   =   4 4 0 2 , 	 / / g�RhV�S�ߍ*��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ S E N D _ M A P S I N F O   =   4 4 0 3 , 	 / / g�RhV�S�0W�VƖ 
 	 J S O N M S G C O D E _ C L I E N T _ T R A C E _ P E R S O N _ R O U T E   =   4 4 0 4 , 	 / / g�RhV�c��bf��Nir�v_ 
 	 J S O N M S G C O D E _ C L I E N T _ T R A C E _ P E R S O N _ E N D   =   4 4 0 5 , 	 / / g�RhV�c��bf��Nir��*��~_g 
  
 	 J S O N M S G C O D E _ C L I E N T _ G E T _ M A P S I N F O _ B A C K   =   4 4 0 6 , 	 / / �[7b�z��Bl0W�V�Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ A L A R M _ D E A L _ B A C K   =   4 4 0 7 , 	 / / �[7b�zYt�bf��Oo`  *gO(u 
 	 J S O N M S G C O D E _ C L I E N T _ T R A C E _ P E R S O N _ C H A N G E _ B A C K   =   4 4 0 8 , 	 / / �[7b�zRbc0Rߍ*�h~{u�c�[ߍ*��g*N�bf�I D  
 	 J S O N M S G C O D E _ C L I E N T _ T E R M I N E R _ T R A C E _ P E R S O N _ B A C K   =   4 4 0 9 , 	 / / �[7b�z�~_g��*��g*N�bf�I D  
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ L O O K _ B A C K _ B A C K   =   4 4 1 0 , 	 / / �[7b�z  �g⋥bf��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ S E C N D _ R G N S _ B A C K   =   4 4 1 1 , 	 / / �[7b�z��Q�Yt  �g⋥bf��Oo`  ���S\:S�WRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ C A M R _ L I S T _ B A C K   =   4 4 1 2 , 	 / / �[7b�z��Q�Yt  �g⋥bf��Oo`  ���S�v:gRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ D E T A I L _ B A C K   =   4 4 1 3 , 	 / / �[7b�z  �g�US*N�bf��Nir�v�bf���~�Oo`( �NT�S���S�bf�Ɖ��Rh�)  
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ V I S E O _ B A C K   =   4 4 1 4 , 	 / / �[7b�z��Q�Yt  z��^/ ��:g�d>e�bf�Ɖ�� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ A L A R A M _ T R A C K E R _ B A C K   =   4 4 1 5 , 	 / / �[7b�z��Q�Yt  >f:y�bf�h��� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ L O O K _ B A C K _ B A C K   =   4 4 1 6 , 	 / / �[7b�z  �g⋓b�b�V 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ S E C N D _ R G N S _ B A C K   =   4 4 1 7 , 	 / / �[7b�z��Q�Yt  �g⋓b�b�V�Oo`  ���S\:S�WRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ C A M R _ L I S T _ B A C K   =   4 4 1 8 , 	 / / �[7b�z��Q�Yt  �g⋓b�b�V�Oo`  ���S�v:gRh� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ L O O K _ P R E V _ B A C K   =   4 4 1 9 , 	 / / �[7b�z�Q�Yt  �g⋓b�b�V
N Nu� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ C A P T U E R _ L O O K _ N E X T _ B A C K   =   4 4 2 0 , 	 / / �[7b�z�Q�Yt  �g⋓b�b�VN Nu� 
 	 J S O N M S G C O D E _ C L I E N T _ S E A R C H _ R E C O R D _ L O O K _ B A C K _ B A C K   =   4 4 2 1 , 	 / / �[7b�z  �g��d\O�e�_ 
 	 J S O N M S G C O D E _ C L I E N T _ A C C O U N T _ C H A N G E _ P A S S W O R D _ B A C K   =   4 4 3 0 , 	 / / �[7b�z�O9e�[x 
 	 J S O N M S G C O D E _ C L I E N T _ L O G _ R E C O R D _ B A C K   =   4 4 3 1 , 	 / / �[7b�z
N O�e�_�Oo` 
 } ;  
  
 e n u m   _ J s o n M s g C o d e W a r n / / �Q�sf�JT�Oo` 
 {  
 	 J S O N M S G C O D E _ C L I E N T _ C O N N E C T _ U P D A T E   =   4 1 0 0 0 , 	 / / �[7b�zޏ�cg�RhVKmՋ��Blb�R�FOHr,g ����f�e 
 	 J S O N M S G C O D E _ C L I E N T _ C O N N E C T _ U P D A T E _ M U S T   =   4 1 0 0 1 , 	 / / �[7b�zޏ�cg�RhVKmՋ��Blb�R�FOHr,g ���:_6R�f�e 
 	 J S O N M S G C O D E _ C L I E N T _ Q U I T _ I S A B O U T L O G O U T   =   4 1 0 0 2 , 	 / / �[7b�z6e0Rg�RhV ��Qc�N�(Wc�[P���eT ��Q 
 	 J S O N M S G C O D E _ C L I E N T _ Q U I T _ L O G O U T N O W   =   4 1 0 0 3 , 	 / / �[7b�z6e0Rg�RhV�zsS ��Qc�N 
 	 J S O N M S G C O D E _ C L I E N T _ A C C O U N T Q U I T _ I S A B O U T L O G O U T   =   4 1 0 0 4 , 	 / / �[7b�z6e0Rg�RhV  &�7b   ��Qc�N�(Wc�[P���eT ��Q 
 	 J S O N M S G C O D E _ C L I E N T _ A C C O U N T Q U I T _ L O G O U T N O W   =   4 1 0 0 5 , 	 / / �[7b�z6e0Rg�RhV  &�7b  �zsS ��Qc�N 
 	 J S O N M S G C O D E _ C L I E N T _ N E W _ W A R N I N F O   =   4 1 0 0 6 , 	 / / 6e0R�e�v�bf��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ M O D I F Y _ W A R N I N F O   =   4 1 0 0 7 , 	 / / 6e0R�O9e�bf��Oo`�v�mo` 
 	 J S O N M S G C O D E _ C L I E N T _ D E L E T E _ W A R N I N F O   =   4 1 0 0 8 , 	 / / 6e0R Rd��bf��Oo`�v�mo` 
 } ;  
  
  
 e n u m   _ J s o n M s g C o d e E r r / / �Q�s���Oo` 
 {  
 	  
 	  
 	  
 	  
 	  
 	  
 	  
 	  
 	  
 	  
 	 J S O N M S G C O D E _ C L I E N T _ L O G I N _ E R R _ U S E R N A M E   =   4 5 0 0 1 , 	 / / �[7b�z{vU_��Bl�(u7bTNX[(W 
 	 J S O N M S G C O D E _ C L I E N T _ L O G I N _ E R R _ P A S S W O R D   =   4 5 0 0 2 , 	 / / �[7b�z{vU_��Bl�(u7bTX[(W��[x�����!kpe\/}�� 
 	 J S O N M S G C O D E _ C L I E N T _ L O G I N _ E R R _ T I M E S L I M I T   =   4 5 0 0 3 , 	 / / �[7b�z{vU_��Bl�(u7bTX[(W��[xcknx�FO/f��!kpe��P���ybk{vF� 
 	 J S O N M S G C O D E _ C L I E N T _ L O G I N _ E R R _ H A V E L O G I N   =   4 5 0 0 4 , 	 / / �[7b�z{vU_��Bl�S_MR&�7b	g(WvQ�N�[7b�z{vF� 
 	 J S O N M S G C O D E _ C L I E N T _ C O N N E C T T E S T _ T I M E O U T   =   4 5 0 0 5 , 	 / / �[7b�zޏ�cg�RhV  KmՋ  ��Bl����e�ޏ�c1Y%� 
 	 J S O N M S G C O D E _ C L I E N T _ A L A R M _ D E A L _ R E S U L T _ F A I L E D   = 4 5 0 0 6 ,   / / �[7b�z��Bl  ߍ*�bb  �g�RhV�b�~���Bl 
 	 J S O N M S G C O D E _ C L I E N T _ A C C O U N T _ O L D _ P A S S W O E D _ E R R   = 4 5 0 0 7 ,   / / �[7b�z��Bl  9e�[  ��e�[x�� 
 	  
 	 J S O N M S G C O D E _ C L I E N T _ F A C E _ 1 V S N _ N O _ S O U R C E _ I M G   =   3 2 5 0 1 , / / �l	g���S0R�V�P 
 	 J S O N M S G C O D E _ C L I E N T _ F A C E _ 1 V S N _ S O U R C E _ I M G _ U N Q U A L I T Y   =   4 6 0 0 2 , / / �N8�(�ϑNT<h 
 	 J S O N M S G C O D E _ C L I E N T _ F A C E _ 1 V S N _ N O _ F A C E _ I N _ S O U R C E _ I M G   =   4 6 0 0 3 , / / �l	g�hKm0R�N8� 
 	 J S O N M S G C O D E _ C L I E N T _ F A C E _ 1 V S N _ N O _ M A C H _ L I B _ I M G   =   4 6 0 0 4 , / / �l	g~b0R9SM��v�N8��Oo` 
 	 J S O N M S G C O D E _ C L I E N T _ N O _ F A C E _ L I B _ I N F O   =   4 6 0 0 5 ,   / / �l	g���S0R�^�Oo` 
 	  
 	 J S O N M S G C O D E _ J S O N P A R S E _ F A I L E D   =   4 8 9 0 0 , 	 / / ���SJ S O N W[&{2N1Y%� 
 } ;  
  
 e n u m   C A M E R A _ S T A T E  
 {  
 	 C A M _ C L O S E D   =   	 	 	 	 0 , 	 	 / / 2 	 *g{vF�0*gޏ�c 
 	 C A M _ O P E N   =   	 	 	 	 	 1 , 	 	 / / 3 	 �]ޏ�c�v:g�FO/f*gU\:y�*g�bf� 
 	 C A M _ W A R N I N G   =   	 	 	 	 2 , 	 	 / / 5 	 �]ޏ�c�v:g�*gU\:y��bf� 
 	 C A M _ S H O W I N G   =   	 	 	 	 3 , 	 	 / / 4 	 �]ޏ�c�v:g�U\:y�*g�bf� 
 	 C A M _ S H O W I N G _ W A R N I N G   =   	 	 4 , 	 	 / / 6 	 �]ޏ�c�v:g�U\:y��bf� 
 } ;  
 e n u m   C A M E R A _ S T A T U S  
 {  
 	 J S O N C A M E R A O N L I N E   =   0 , / / o n   l i n e    
 	 J S O N C A M E R A O F F L I N E   =   1 , / / o f f   l i n e  
 } ;  
 e n u m   _ C h a n g e F a c e d e t e c t i o n C a m e r a  
 {  
 	 C H A N G E _ F A C E D E T E C T I O N _ C A M E R A _ T Y P E _ A D D   =   0 ,   / / �m�R�v:g   
 	 C H A N G E _ F A C E D E T E C T I O N _ C A M E R A _ T Y P E _ D E L E T E   =   1 ,   / /  Rd��v:g 
 	 C H A N G E _ F A C E D E T E C T I O N _ C A M E R A _ T Y P E _ R E V I S E   =   2 ,   / / �O9e�v:g 
 	 C H A N G E _ F A C E D E T E C T I O N _ C A M E R A _ T Y P E _ I N I   =   3 ,   / / R�YS�e�v:g 
 } ;  
  
 e n u m   _ C h a n g e C a m e r a E r r T y p e  
 {  
 	 C A M E R A _ C O N N E C T _ E R R   =   1 , / / �v:g���c�� 
 	 C A M E R A _ C O N N E C T _ T I M E _ O U T   =   2 / / �v:g���c�� 
 } ;  
 t y p e d e f   s t r u c t   _ C a m e r a S t a t e I n f o  
 {  
 	 s t r i n g 	 c a m N a m e ; 	 	 / / �v:gT 
 	 u n s i g n e d   i n t 	 c a m I D ; 	 	 	 / / �v:g/U N�S 
  
 	 s t r i n g 	 c a m U s e r N a m e ;  
 	 s t r i n g 	 c a m P a s s W o r d ;  
 	 s t r i n g 	 c a m I P ; 	 	 	 / / �v:gI P  
 	 u n s i g n e d   i n t 	 c a m P o r t ; 	 	 / / �v:g�z�S 
  
 	 s t r i n g 	 m e d i a U s e r N a m e ; 	 / / �ZSOg�RhV{vF�(u7bT 
 	 s t r i n g 	 m e d i a P a s s W o r d ; 	 / / �ZSOg�RhV{vF��[x 
 	 s t r i n g 	 m e d i a I P ; 	 	 	 / / �ZSOg�RhVI P  
 	 u n s i g n e d   i n t 	 m e d i a P o r t ; 	 	 / / �ZSOg�RhV�z�S 
  
 	 s t r i n g 	 c a m M a p N a m e ; 	 	 / / :S�WT�0W�VT 
 	 u n s i g n e d   i n t 	 c a m M a p X ; 	 	 / / �v:g(W�v�c0W�V�vx PWh 
 	 u n s i g n e d   i n t 	 c a m M a p Y ; 	 	 / / �v:g(W�v�c0W�V�vy PWh 
 	 u n s i g n e d   i n t 	 c a m S t a t e ; 	 	 / / �v:g�r`�C A M _ C L O S E D   C A M _ O P E N   C A M _ W A R N I N G  
 	 u n s i g n e d   i n t 	 s t r e a m T y p e ; 	 	 / / �v:gxAm{|�W�H 2 6 4 , H 2 6 5  
 } C a m e r a S t a t e I n f o ;  
  
 # i f n d e f   _ _ S T R E A M _ T Y P E _ _  
 # d e f i n e   _ _ S T R E A M _ T Y P E _ _  
 e n u m   _ S t r e a m T y p e  
 {  
 	 S T R E A M _ T Y P E _ 2 6 4   =   2 6 4 ,  
 	 S T R E A M _ T Y P E _ 2 6 5   =   2 6 5 ,  
 } ;  
 # e n d i f  
  
 / *  
 t y p e d e f   s t r u c t   D I S T R I C T _ M A P S _ I N F O  
 {  
 s t r i n g 	 m a p U r l ;  
 } D i s t r i c t M a p s I n f o ;  
  
 t y p e d e f   s t r u c t   C A M S I N F O  
 {  
 s t d : : m a p < D W O R D ,   C a m e r a S t a t e I n f o   * >   c a m s ;  
 } C a m s I n f o ;  
 t y p e d e f   s t r u c t   D I S I N F O  
 {  
 s t d : : m a p < s t d : : s t r i n g ,   C a m s I n f o >   d i s ;  
 } D i s I n f o ;  
 t y p e d e f   s t r u c t   E A R A I N F O  
 {  
 s t d : : m a p < s t d : : s t r i n g ,   D i s I n f o >   e a r a s ;  
 } E a r a I n f o ;  
 * /  
 # e n d i f 	 / / _ _ M S G _ D E F I N E _ _  
 