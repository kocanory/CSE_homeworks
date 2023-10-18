package project;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Vector;

import javax.swing.*;


public class MainFrame extends JFrame implements ActionListener{
	
	Editor e = new Editor(); //Editor 클래스의 객체 생성
	Vector<String> strList = new Vector<String>(); //스크롤바 생성을 위해 벡터 생성
	JPanel content = new JPanel(); //패널 생성
	JTextArea info = new JTextArea(15, 30); //텍스트영역 생성
	JMenuBar myMenu = new JMenuBar();// 메뉴바 생성
	JMenu mn_file = new JMenu("파일"); //파일 메뉴 생성
	JMenu mn_edit = new JMenu("편집"); //편집 메뉴 생성
	
	JButton input = new JButton("입력"); //입력 버튼 생성
	JButton search= new JButton("검색"); //검색 버튼 생성
	JButton replace= new JButton("변경"); //변경 버튼 생성
	JButton insertion = new JButton("삽입"); //삽입 버튼 생성
	JButton output= new JButton("출력"); //출력 버튼 생성
	JTextField file_address = new JTextField(10); //텍스트를 입력할 수 있는 텍스트필드 생성
	JTextField word = new JTextField(10); //텍스트필드 생성
	JTextField number = new JTextField(6); //텍스트필드 생성
	JTextArea timer = new JTextArea(1,5); //텍스트영역 생성
	
	JList list = new JList(); //리스트 생성
	JScrollPane scroller = new JScrollPane(list); //스크롤바 생성
	
	void scrollbar()
	{
		scroller.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS); //세로 스크롤 설정
		scroller.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS); //가로 스크롤 설정
		list.setVisibleRowCount(10); //한번에 보여지는 스크롤수 설정
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION); //스크롤 중 하나만 선택가능하게 함
	}
	public MainFrame(String title) {
		super(title); //슈퍼클래스의 생성자 실행
		myMenu.add(new JLabel("파일 경로 입력 ")); //
		myMenu.add(file_address);
		myMenu.add(mn_file);
		myMenu.add(new JLabel("                             "));
		myMenu.add(new JLabel("단어 입력 "));
		myMenu.add(word);
		myMenu.add(new JLabel("   "));
		myMenu.add(new JLabel("삽입할 곳  "));
		myMenu.add(number);
		myMenu.add(mn_edit); //메뉴바에 파일 경로 입력칸, 단어입력칸, 삽일할 위치 칸 등 추가
		content.add(myMenu);
		content.add(info);
		content.add(scroller);
		content.add(new JLabel("검색 시간 "));
		content.add(timer); //패널에 메뉴, 정보표시판, 스크롤, 검색시간 표시칸을 추가
		mn_edit.add(search);
		mn_edit.add(replace);
		mn_edit.add(insertion);
		mn_file.add(input);
		mn_file.add(output); //파일, 편집 메뉴에 버튼들 추가
		info.setText("파일 경로를 입력하시오."); //정보표시판에 출력
		content.setLayout((new FlowLayout()));
		add(content);	
		strList.add("----------------------------------목록-------------------------------");
		list.setListData(strList); //매개변수로 주어진 벡터를 리스트에 입력
		
		scrollbar();//스크롤바 메소드 실행
		input.addActionListener(this);
		search.addActionListener(this);
		replace.addActionListener(this);
		output.addActionListener(this);
		insertion.addActionListener(this);
	}
	
	String getTime(long startTime)
	{
		long getTime = System.currentTimeMillis() - startTime;
		return Float.toString(getTime); //소요시간을 스트링으로 리턴
	}
	
	public void actionPerformed(ActionEvent event)
	{		
			if(event.getSource() == input)
			{
				if(file_address.getText().equals(e.TEXT_PATH)) 
			{
				info.setText("파일이 존재합니다.");//입력한 경로가 맞을경우 파일 존재 메시지 출력
				
				try {
					e.in = new FileInputStream(e.TEXT_PATH);//파일 입력 기능을 위한 객체를 생성 및 초기화, 텍스트 파일을 불러옴;
					while(e.in.read(e.readBuffer, 0,  e.readBuffer.length) != -1)
					{
						e.strTemp = new String(e.readBuffer); // String 객체를 생성 및 초기화, test.txt 내용을 저장 
					}
				} catch (IOException e) { //예외가 발생할 경우 printStackTrace 실행
					e.printStackTrace();
				}
				
				e.temp = new String(e.strTemp);
				info.setText("검색할 단어를 입력하세요. ");
			}
			else
			{	
				
			  info.setText("파일이 존재하지 않습니다. 경로를 다시 입력하세요: "); //파일명이 다를 경우 출력
						
			}
		}

		else if(event.getSource() == search)
		{
			try {
				long startTime = System.currentTimeMillis();
				e.writer = new FileWriter(e.FILE_OUT_PATH);//파일 입력 기능을 위한 객체를 생성 및 초기화
				e.strTemp = e.strTemp.replaceAll("\r\n", ""); //중간에 줄바꿈이 있다면 제거
				e.compare = e.strTemp.indexOf(word.getText()); //test.txt 내용과 자신이 입력한 문자열을 비교
				e.input = word.getText();
				if(e.compare != -1)
				{
					e.num = new int[word.getText().length()];
					for(int i = 0;i < word.getText().length() ; i++)
					{
						e.num[i] = e.compare + i; //index를 배열에 저장
					}
					
					info.setText("index : " + e.num[0] + " ~ " + e.num[word.getText().length() - 1]); //index를 정보표시판에 출력
					strList.add("index of "+ word.getText() + " is " + e.num[0] + " ~ " + e.num[word.getText().length() - 1]); //벡터에 index 저장
					list.setListData(strList); //리스트에 추가
					timer.setText(getTime(startTime));	//소요시간 계산 및 출력			
				}
				else
				{
					timer.setText(getTime(startTime)); //소요시간 계산 및 출력
					info.setText("not existance"); //만약 문자열이 test.txt에 없을 경우 출력		
					e.writer.write("not existance");
				}							
						e.in.close();//파일 입력 종료
						e.bufferedInputStream.close(); //파일 입력 종료	
						e.writer.close();//파일 쓰기 종료
					}
		catch (IOException e) { //예외가 발생할 경우 printStackTrace 실행
				e.printStackTrace();
			}
		}
		
		else if(event.getSource() == replace)
		{
			e.strTemp = e.strTemp.replace(e.input, word.getText()); //입력한 단어로 교체
			info.setText("Replacing successed"); //교체 메시지 출력
		}
			
		else if(event.getSource() == insertion)
		{
			StringBuffer sb = new StringBuffer(e.strTemp); //스트링버퍼 객체 생성
			sb.insert(Integer.parseInt(number.getText()), word.getText());//입력받은 위치에 단어를 삽입
			e.strTemp = sb.toString(); //스트링 버퍼를 스트링으로 변환하여 원래 있던 스트링에 저장
			info.setText("Insertion successed");//삽입 메시지 출력
		}
			
		else if(event.getSource() == output)
		{
			try {
				e.wt = new FileWriter(file_address.getText()); //파일 입력을 위한 객체를 생성 및 초기화
				e.wt.write(e.strTemp);//앞서 바뀐 문자열을 파일에 저장
				e.wt.close();//파일 쓰기 종료
				info.setText("File output stream successed");//출력 메시지 출력
			} catch (IOException e) { //예외가 발생할 경우 printStackTrace 실행
				e.printStackTrace();
			}	
		}
		
	}

	public static void main(String[] args) {
		MainFrame f = new MainFrame("메뉴");
		f.setSize(700, 400);
		f.setDefaultCloseOperation(EXIT_ON_CLOSE);
		f.setVisible(true);
	}

}
