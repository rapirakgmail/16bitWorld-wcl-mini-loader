# wcl-mini-loader
# รายละเอียด
    - วัตถุประสงค์เพื่อเสริมความเข้าใจเกี่ยวกับกลไกลการทำงานของ loader module ของระบบปฎิบัติการ
    - โปรแกรมรองรับเฉพาะระบบปฎิบัติการ DOS 16 bit หรือ DOXBOX
    - โปรแกรมรองรับเฉพาะการโหลดแฟ้ม ".COM" เท่านั้น
    - พัฒนาโดยใช้  Watcom C/C++ 

# แฟ้ม
  1. WCLOADER.C  : source file ของ loader 
     การ compile
      - wcl wcloader.c    (ได้ wcloader.exe)
      - หรือ c.bat 
  3. APP2.C : source file ของโปรแกรมตัวอย่าง  
     การ compile ใช้ tiny model 
      - wcl -mt app2.c (ได้ app2.exe)
        exe2bin app2.exe app2.com
      - หรือ b.bat

 4. dosbox-wcl.zip : Zip file ที่ประกอบด้วย folder
    - DPRJ  : เก็บ source file ของ wcloader.c และ APP2.c  
    - tools : utility programs
    - WATCOM: Watcom C/C++ ที่พร้อมใช้งาน
    - AUTOEXEC.BAT : ไฟล์ "BAT" ทำหน้าที่ set path โดยให้สั่ง run เป็นลำดับแรก
      
 5. NOTE :
     1. exe2bin โปรแกรมที่ทำหน้าที่แปลง ".EXE" ให้เป็น ".COM"
     2. คู่มือการใช้ Watcom C/C++ https://open-watcom.github.io/open-watcom-v2-wikidocs/ctools.pdf
     3. สามารถเตรียมเครื่องมือต่างๆสำหรับการ compile ได้ โดย download แฟ้มทั้งหมดจาก https://github.com/rapirakgmail/wcl-env

 # ขั้นตอนการเตรียม enviroment
     1. ติดตั้ง DOSBOX หรือสร้าง VM ของ DOS16bit ตั้งแต่ 3.x หรือ freedos
     2. สามารถทำได้ 2 วิธี
         2.1. download dosbox-wcl.zip และนำมาแตกไฟล์ที่ drive c และทุกครั้งให้เรียกโปรแกรม AUTOEXEC.BAT เพื่อ set path
         2.2. download zip file จาก "https://github.com/rapirakgmail/wcl-env"  และนำมาแตกไฟล์ที่ drive c
              และ download "WCLOADER.C" และ "AP2.C" 
         
