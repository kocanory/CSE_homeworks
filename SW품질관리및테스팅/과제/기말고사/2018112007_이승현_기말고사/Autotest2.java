import org.sikuli.script.Env;
import org.sikuli.script.Key;

public class Autotest2 {
	private void run()
	{
		tab1();
		tab2_ver2();
		tab3_ver2();
		tab4_ver2();
		tab5();
		tab6_ver2();
		tab7();
		tab8();
		tab9();
	}
	private void tab1()
	{
		boolean succeeded = true;
		String array[] = {"TextEditorTab.png", "LoremIpsumTab.png", "ColorPickerTab.png", "ProgressTab.png"};
		int i = 0;
		
		while(succeeded && i < array.length)
		{
			sikuli.click(array[i]);
			sikuli.click("KoalaTab.png");
			succeeded = sikuli.verifyIfExists("koala.png");
			i++;
		}		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 1", "Koala was the same");
		} else {
			reportFile.add("FAILED", "Tab 1", "Koala was not the same");
		}
	}
	
	private void tab2_ver2()
	{
		sikuli.click("TextEditorTab.png");
		
		boolean succeeded = true;

		String array[] = {"HTMLeditor_ver2_1.png", "HTMLeditor_ver2_2.png"};
		int i = 0;
		while(succeeded && i < array.length)
		{
			succeeded = sikuli.verifyIfExists(array[i]);
			i++;
		}
		if (succeeded) {
			reportFile.add("PASSED", "Tab 2", "HTML editor contained buttons");
		} else {
			reportFile.add("FAILED", "Tab 2", "HTML editor did not contain buttons");
		}
		
		sikuli.click("KoalaTab.png");
	}
	
	private void tab3_ver2()
	{
		boolean succeeded = true;
		String array[] = {"KoalaTab.png", "LoremIpsumTab.png", "ColorPickerTab.png", "ProgressTab.png"};
		int i = 0;
		
		sikuli.click("TextEditorTab.png");
		if(sikuli.write("writeSomething_ver2.png", "I am writing here")) {
			System.out.println("Using resolution 1920 x 1080 picture");
		} else {
			System.out.println("Using resolution 1366 x 768 picture");			
			sikuli.write("writeSomethingLower_ver2.png", "I am writing here");
		}
		
		while(succeeded && i < array.length)
		{
			sikuli.click(array[i]);
			sikuli.click("TextEditorTab.png");
			succeeded = sikuli.click("WroteSomething_ver2.png");
			if (succeeded)
			{
				succeeded = sikuli.compareTextToClipboards("I am writing here");
			}
			i++;
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 3", "Entered text was the same");
		} else {
			reportFile.add("FAILED", "Tab 3", "Entered text was not the same");
			}
		sikuli.click("WroteSomething_ver2.png");
		sikuli.click("KoalaTab.png");
	}
	
	private void tab4_ver2()
	{
	
		boolean succeeded = true;
		String array1[] = {"KoalaTab.png", "LoremIpsumTab.png", "ColorPickerTab.png", "ProgressTab.png"};
		int i = 0;
		
		sikuli.click("TextEditorTab.png");
		
		while(succeeded && i < array1.length)
		{
			sikuli.click(array1[i]);
			sikuli.click("TextEditorTab.png");
			succeeded = sikuli.verifyIfExists("WroteSomething_ver2.png");	
			i++;		
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 4", "Text formatting setting was the same");
		} else {
			reportFile.add("FAILED", "Tab 4", "Text formatting setting was not the same");
			}
		sikuli.click("KoalaTab.png");
	}
	
	private void tab5()
	{
		boolean succeeded = true;
		String array[] = {"KoalaTab.png", "TextEditorTab.png", "ColorPickerTab.png", "ProgressTab.png"};
		int i = 0;
		
		sikuli.click("LoremIpsumTab.png");
		sikuli.click("LoremIpsumText.png");
		sikuli.screen.type("a", Key.CTRL);
		sikuli.screen.type("c", Key.CTRL);
		String textFromSikuli = Env.getClipboard();
		
		while(succeeded && i < array.length)
		{
			sikuli.click(array[i]);
			sikuli.click("LoremIpsumTab.png");
			if(sikuli.verifyIfExists("LoremIpsumText_AllSelected.png")) sikuli.click("LoremIpsumText_AllSelected.png"); 
			else sikuli.click("LoremIpsumText.png");
			succeeded = sikuli.compareTextToClipboards(textFromSikuli);
			i++;		
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 5", "Text Length was the same");
		} else {
			reportFile.add("FAILED", "Tab 5", "Text Length was not the same");
			}
		sikuli.click("KoalaTab.png");

	}
	
	private void tab6_ver2()
	{		
		boolean succeeded = true;
		int i = 0;
		sikuli.click("LoremIpsumTab.png");
		
		while(succeeded && i < 2)
		{
			
			if(i == 0)
			{
				sikuli.click("LoremIpsumText.png");
				sikuli.rightClick();
				sikuli.click("Scrollbar.png");
				sikuli.click("AllSelect.png");
				succeeded = sikuli.verifyIfExists("LoremIpsumText_AllSelected.png");
			}
			else
			{
				sikuli.rightClick();
				sikuli.click("Scrollbar.png");
				sikuli.click("Copy.png");
				String textFromSikuli = Env.getClipboard();
				if (textFromSikuli.isEmpty()) succeeded = false;
				else succeeded = true;
			}
			i++;
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 6", "Selected all a Context menu");
		} else {
			reportFile.add("FAILED", "Tab 6", "Did not select a Context menu");
			}
		sikuli.click("KoalaTab.png");
	}
	
	private void tab7()
	{
		boolean succeeded = true;
		int i = 0;
		sikuli.click("ColorPickerTab.png");
		
		while(succeeded && i < 3)
		{
			
			if(i == 0)
			{
				succeeded = sikuli.verifyIfExists("Folded.png");
				if(!succeeded) break;
				succeeded = sikuli.verifyIfExists("Folded_Color.png");
			}
			else if(i == 1)
			{
				sikuli.click("Folded.png");
				succeeded = sikuli.verifyIfExists("Extend.png");
				if(!succeeded) break;
				succeeded = sikuli.verifyIfExists("Folded_Color.png");
				succeeded = !succeeded;
			}
			else
			{
				sikuli.click("Extend.png");
				succeeded = sikuli.verifyIfExists("Folded.png");
				if(!succeeded) break;
				succeeded = sikuli.verifyIfExists("Folded_Color.png");
			}
			i++;		
		}
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 7", "Color Picker tab was collapsible");
		} else {
			reportFile.add("FAILED", "Tab 7", "Color Picker tab was not collapsible");
			}
		sikuli.click("KoalaTab.png");
	}
	
	private void tab8()
	{
		boolean succeeded = true;
		String array[] = {"KoalaTab.png", "TextEditorTab.png", "LoremIpsumTab.png", "ProgressTab.png"};
		int i = 0;
		
		sikuli.click("ColorPickerTab.png");
		sikuli.click("Folded.png");
		
		while(succeeded && i < array.length)
		{
			sikuli.click(array[i]);
			sikuli.click("ColorPickerTab.png");
			succeeded = sikuli.verifyIfExists("Extend_Color.png");
			i++;
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 8", "Selected color was the same");
			} else {
			reportFile.add("FAILED", "Tab 8", "Selected color was not the same");
			}
		sikuli.click("KoalaTab.png");
	}
	
	private void tab9()
	{
		boolean succeeded = true;
		boolean succeeded1 = true;
		boolean succeeded2 = true;
		String array1[] = {"KoalaTab.png", "TextEditorTab.png", "LoremIpsumTab.png", "ColorPickerTab.png"};
		String array2[] = {"Progress_1.png", "Progress_2.png"};
		int i = 0;
		
		sikuli.click("ProgressTab.png");
		
		while(succeeded && i < array1.length)
		{
			sikuli.click(array1[i]);
			sikuli.click("ProgressTab.png");
			succeeded1 = sikuli.verifyIfExistsReTried(array2[0], 10);
			succeeded2 = sikuli.verifyIfExistsReTried(array2[1], 10);
			succeeded = succeeded1 && succeeded2;
			i++;
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 9", "Loader bar was in the infinite state");
			} else {
			reportFile.add("FAILED", "Tab 9", "Loader bar was not in the infinite state");
			}
		sikuli.click("KoalaTab.png");

	}
}
