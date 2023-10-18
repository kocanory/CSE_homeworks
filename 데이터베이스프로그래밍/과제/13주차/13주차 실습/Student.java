package studentBean;

public class Student {
	private String s_name;
	private String s_address;
	private String s_pwd;
	private String s_college;
    private String s_major;

	public Student() {
		s_name = null;
		s_address = null;
		s_pwd = null;
		s_college = null;
        s_major = null;
	}

	public void setName(String s_name) {
		this.s_name = s_name;
	}

	public void setAddress(String s_address) {
		this.s_address = s_address;
	}

	public void setPwd(String s_pwd) {
		this.s_pwd = s_pwd;
	}

	public void setCollege(String s_college) {
		this.s_college = s_college;
	}

    public void setMajor(String s_major) {
		this.s_major = s_major;
	}

	public String getName() {
		return s_name;
	}

	public String getAddress() {
		return s_address;
	}

	public String getPwd() {
		return s_pwd;
	}

	public String getCollege() {
		return s_college;
	}

    public String getMajor() {
		return s_major;
	}
}