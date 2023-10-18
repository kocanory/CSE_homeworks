import org.sikuli.script.Env;
import org.sikuli.script.Key;

public class Autotest1 {
	
	private void run()
	{
		tab1();
		tab2();
		tab3();
		tab4();
		tab5();
		tab6();
		tab7();
		tab8();
	}
	private void tab1()
	{
		boolean succeeded = true;
		String array[] = {"TextEditorTab.png", "LoremIpsumTab.png", "ColorPickerTab.png"};
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
	
	private void tab2()
	{
		sikuli.click("TextEditorTab.png");
		
		boolean succeeded = true;

		String array[] = {"HTMLeditor_1.png", "HTMLeditor_2.png"};
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
	
	private void tab3()
	{
		boolean succeeded = true;
		String array[] = {"KoalaTab.png", "LoremIpsumTab.png", "ColorPickerTab.png"};
		int i = 0;
		
		sikuli.click("TextEditorTab.png");
		if(sikuli.write("writeSomething.png", "I am writing here")) {
			System.out.println("Using resolution 1920 x 1080 picture");
		} else {
			System.out.println("Using resolution 1366 x 768 picture");			
			sikuli.write("writeSomethingLower.png", "I am writing here");
		}
		
		while(succeeded && i < array.length)
		{
			sikuli.click(array[i]);
			sikuli.click("TextEditorTab.png");
			succeeded = sikuli.click("WroteSomething.png");
			if (succeeded)
			{
				succeeded = sikuli.compareTextToClipboards("I am writing here");
				sikuli.screen.type("v", Key.CTRL);
			}
			i++;
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 3", "Entered text was the same");
		} else {
			reportFile.add("FAILED", "Tab 3", "Entered text was not the same");
			}
		sikuli.click("WroteSomething.png");
		sikuli.click("KoalaTab.png");
	}
	
	private void tab4()
	{		
		boolean succeeded = true;
		String array1[] = {"KoalaTab.png", "LoremIpsumTab.png", "ColorPickerTab.png"};
		int i = 0;
		
		sikuli.click("TextEditorTab.png");
		
		while(succeeded && i < array1.length)
		{
			sikuli.click(array1[i]);
			sikuli.click("TextEditorTab.png");
			int j = 0;
			succeeded = sikuli.verifyIfExists("WroteSomething.png");
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
		String array[] = {"KoalaTab.png", "TextEditorTab.png", "ColorPickerTab.png"};
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
	
	private void tab6()
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
				succeeded = sikuli.verifyIfExists("Context1.png");
			}
			else
			{
				sikuli.click("AllSelect.png");
				sikuli.rightClick();
				sikuli.click("Scrollbar.png");
				succeeded = sikuli.verifyIfExists("Context2.png");
			}
			i++;
		}	
		
		if (succeeded) {
			reportFile.add("PASSED", "Tab 6", "Textarea had a Context menu");
		} else {
			reportFile.add("FAILED", "Tab 6", "Textarea did not have a Context menu");
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
		String array[] = {"KoalaTab.png", "TextEditorTab.png", "LoremIpsumTab.png"};
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
}
