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
	
	Editor e = new Editor(); //Editor Ŭ������ ��ü ����
	Vector<String> strList = new Vector<String>(); //��ũ�ѹ� ������ ���� ���� ����
	JPanel content = new JPanel(); //�г� ����
	JTextArea info = new JTextArea(15, 30); //�ؽ�Ʈ���� ����
	JMenuBar myMenu = new JMenuBar();// �޴��� ����
	JMenu mn_file = new JMenu("����"); //���� �޴� ����
	JMenu mn_edit = new JMenu("����"); //���� �޴� ����
	
	JButton input = new JButton("�Է�"); //�Է� ��ư ����
	JButton search= new JButton("�˻�"); //�˻� ��ư ����
	JButton replace= new JButton("����"); //���� ��ư ����
	JButton insertion = new JButton("����"); //���� ��ư ����
	JButton output= new JButton("���"); //��� ��ư ����
	JTextField file_address = new JTextField(10); //�ؽ�Ʈ�� �Է��� �� �ִ� �ؽ�Ʈ�ʵ� ����
	JTextField word = new JTextField(10); //�ؽ�Ʈ�ʵ� ����
	JTextField number = new JTextField(6); //�ؽ�Ʈ�ʵ� ����
	JTextArea timer = new JTextArea(1,5); //�ؽ�Ʈ���� ����
	
	JList list = new JList(); //����Ʈ ����
	JScrollPane scroller = new JScrollPane(list); //��ũ�ѹ� ����
	
	void scrollbar()
	{
		scroller.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS); //���� ��ũ�� ����
		scroller.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS); //���� ��ũ�� ����
		list.setVisibleRowCount(10); //�ѹ��� �������� ��ũ�Ѽ� ����
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION); //��ũ�� �� �ϳ��� ���ð����ϰ� ��
	}
	public MainFrame(String title) {
		super(title); //����Ŭ������ ������ ����
		myMenu.add(new JLabel("���� ��� �Է� ")); //
		myMenu.add(file_address);
		myMenu.add(mn_file);
		myMenu.add(new JLabel("                             "));
		myMenu.add(new JLabel("�ܾ� �Է� "));
		myMenu.add(word);
		myMenu.add(new JLabel("   "));
		myMenu.add(new JLabel("������ ��  "));
		myMenu.add(number);
		myMenu.add(mn_edit); //�޴��ٿ� ���� ��� �Է�ĭ, �ܾ��Է�ĭ, ������ ��ġ ĭ �� �߰�
		content.add(myMenu);
		content.add(info);
		content.add(scroller);
		content.add(new JLabel("�˻� �ð� "));
		content.add(timer); //�гο� �޴�, ����ǥ����, ��ũ��, �˻��ð� ǥ��ĭ�� �߰�
		mn_edit.add(search);
		mn_edit.add(replace);
		mn_edit.add(insertion);
		mn_file.add(input);
		mn_file.add(output); //����, ���� �޴��� ��ư�� �߰�
		info.setText("���� ��θ� �Է��Ͻÿ�."); //����ǥ���ǿ� ���
		content.setLayout((new FlowLayout()));
		add(content);	
		strList.add("----------------------------------���-------------------------------");
		list.setListData(strList); //�Ű������� �־��� ���͸� ����Ʈ�� �Է�
		
		scrollbar();//��ũ�ѹ� �޼ҵ� ����
		input.addActionListener(this);
		search.addActionListener(this);
		replace.addActionListener(this);
		output.addActionListener(this);
		insertion.addActionListener(this);
	}
	
	String getTime(long startTime)
	{
		long getTime = System.currentTimeMillis() - startTime;
		return Float.toString(getTime); //�ҿ�ð��� ��Ʈ������ ����
	}
	
	public void actionPerformed(ActionEvent event)
	{		
			if(event.getSource() == input)
			{
				if(file_address.getText().equals(e.TEXT_PATH)) 
			{
				info.setText("������ �����մϴ�.");//�Է��� ��ΰ� ������� ���� ���� �޽��� ���
				
				try {
					e.in = new FileInputStream(e.TEXT_PATH);//���� �Է� ����� ���� ��ü�� ���� �� �ʱ�ȭ, �ؽ�Ʈ ������ �ҷ���;
					while(e.in.read(e.readBuffer, 0,  e.readBuffer.length) != -1)
					{
						e.strTemp = new String(e.readBuffer); // String ��ü�� ���� �� �ʱ�ȭ, test.txt ������ ���� 
					}
				} catch (IOException e) { //���ܰ� �߻��� ��� printStackTrace ����
					e.printStackTrace();
				}
				
				e.temp = new String(e.strTemp);
				info.setText("�˻��� �ܾ �Է��ϼ���. ");
			}
			else
			{	
				
			  info.setText("������ �������� �ʽ��ϴ�. ��θ� �ٽ� �Է��ϼ���: "); //���ϸ��� �ٸ� ��� ���
						
			}
		}

		else if(event.getSource() == search)
		{
			try {
				long startTime = System.currentTimeMillis();
				e.writer = new FileWriter(e.FILE_OUT_PATH);//���� �Է� ����� ���� ��ü�� ���� �� �ʱ�ȭ
				e.strTemp = e.strTemp.replaceAll("\r\n", ""); //�߰��� �ٹٲ��� �ִٸ� ����
				e.compare = e.strTemp.indexOf(word.getText()); //test.txt ����� �ڽ��� �Է��� ���ڿ��� ��
				e.input = word.getText();
				if(e.compare != -1)
				{
					e.num = new int[word.getText().length()];
					for(int i = 0;i < word.getText().length() ; i++)
					{
						e.num[i] = e.compare + i; //index�� �迭�� ����
					}
					
					info.setText("index : " + e.num[0] + " ~ " + e.num[word.getText().length() - 1]); //index�� ����ǥ���ǿ� ���
					strList.add("index of "+ word.getText() + " is " + e.num[0] + " ~ " + e.num[word.getText().length() - 1]); //���Ϳ� index ����
					list.setListData(strList); //����Ʈ�� �߰�
					timer.setText(getTime(startTime));	//�ҿ�ð� ��� �� ���			
				}
				else
				{
					timer.setText(getTime(startTime)); //�ҿ�ð� ��� �� ���
					info.setText("not existance"); //���� ���ڿ��� test.txt�� ���� ��� ���		
					e.writer.write("not existance");
				}							
						e.in.close();//���� �Է� ����
						e.bufferedInputStream.close(); //���� �Է� ����	
						e.writer.close();//���� ���� ����
					}
		catch (IOException e) { //���ܰ� �߻��� ��� printStackTrace ����
				e.printStackTrace();
			}
		}
		
		else if(event.getSource() == replace)
		{
			e.strTemp = e.strTemp.replace(e.input, word.getText()); //�Է��� �ܾ�� ��ü
			info.setText("Replacing successed"); //��ü �޽��� ���
		}
			
		else if(event.getSource() == insertion)
		{
			StringBuffer sb = new StringBuffer(e.strTemp); //��Ʈ������ ��ü ����
			sb.insert(Integer.parseInt(number.getText()), word.getText());//�Է¹��� ��ġ�� �ܾ ����
			e.strTemp = sb.toString(); //��Ʈ�� ���۸� ��Ʈ������ ��ȯ�Ͽ� ���� �ִ� ��Ʈ���� ����
			info.setText("Insertion successed");//���� �޽��� ���
		}
			
		else if(event.getSource() == output)
		{
			try {
				e.wt = new FileWriter(file_address.getText()); //���� �Է��� ���� ��ü�� ���� �� �ʱ�ȭ
				e.wt.write(e.strTemp);//�ռ� �ٲ� ���ڿ��� ���Ͽ� ����
				e.wt.close();//���� ���� ����
				info.setText("File output stream successed");//��� �޽��� ���
			} catch (IOException e) { //���ܰ� �߻��� ��� printStackTrace ����
				e.printStackTrace();
			}	
		}
		
	}

	public static void main(String[] args) {
		MainFrame f = new MainFrame("�޴�");
		f.setSize(700, 400);
		f.setDefaultCloseOperation(EXIT_ON_CLOSE);
		f.setVisible(true);
	}

}
