package robot;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JRadioButton;
import javax.swing.JScrollBar;
import javax.swing.JTextField;
import javax.swing.ListModel;

import bluetooth.Bluetooth;
import javax.swing.JScrollPane;

public class HlavneOkno {
	
	// pokus

	private Bluetooth bluetooth = Bluetooth.priprav();
	private JFrame frmOvladacRobota;
	private JTextField textVzdialenost;
	private DefaultListModel listModel;
	private JList list;
	private JScrollPane scrollPane;
	private JCheckBox chckbxZastavRolovanie;
	private JCheckBox chckbxZastavPrimanie;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					HlavneOkno window = new HlavneOkno();
					window.frmOvladacRobota.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public HlavneOkno() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmOvladacRobota = new JFrame();
		frmOvladacRobota.setTitle("ovladac robota");
		frmOvladacRobota.setForeground(Color.WHITE);
		frmOvladacRobota.setBounds(100, 100, 1009, 498);
		frmOvladacRobota.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JButton btnNewButton = new JButton("STOP");
		btnNewButton.setToolTipText("zastavit robota");
		btnNewButton.setBounds(840, 367, 78, 44);
		btnNewButton.setBackground(Color.RED);
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				bluetooth.posli("E");
			}
		});
		frmOvladacRobota.getContentPane().setLayout(null);
		frmOvladacRobota.getContentPane().add(btnNewButton);
		
		JButton btnVl = new JButton("vl");
		btnVl.setToolTipText("vlavo");
		btnVl.setBounds(776, 367, 64, 44);
		btnVl.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				bluetooth.posli("C");
			}
		});
		btnVl.setBackground(Color.YELLOW);
		frmOvladacRobota.getContentPane().add(btnVl);
		
		JButton btnVp = new JButton("vp");
		btnVp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				bluetooth.posli("B");
			}
		});
		btnVp.setToolTipText("vpravo");
		btnVp.setBounds(919, 367, 64, 44);
		btnVp.setBackground(Color.YELLOW);
		frmOvladacRobota.getContentPane().add(btnVp);
		
		JButton btnDz = new JButton("dz");
		btnDz.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				bluetooth.posli("D");
			}
		});
		btnDz.setToolTipText("dozadu");
		btnDz.setBounds(850, 408, 64, 44);
		btnDz.setBackground(Color.YELLOW);
		frmOvladacRobota.getContentPane().add(btnDz);
		
		JButton btnDp = new JButton("dp");
		btnDp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				bluetooth.posli("A");
			}
		});
		btnDp.setToolTipText("dopredu");
		btnDp.setBounds(845, 325, 64, 44);
		btnDp.setBackground(Color.YELLOW);
		frmOvladacRobota.getContentPane().add(btnDp);
		
		textVzdialenost = new JTextField();
		textVzdialenost.setBounds(167, 429, 599, 23);
		textVzdialenost.setEditable(false);
		frmOvladacRobota.getContentPane().add(textVzdialenost);
		textVzdialenost.setColumns(10);
		
		JLabel lblVzdialenosOdPrekky = new JLabel("Vzdialenos\u0165 od prek\u00E1\u017Eky:");
		lblVzdialenosOdPrekky.setBounds(10, 430, 165, 21);
		frmOvladacRobota.getContentPane().add(lblVzdialenosOdPrekky);
	    
	    final JRadioButton rdbtnNr = new JRadioButton("najrychlejsie");
	    rdbtnNr.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnNr.isSelected()) {
	    			bluetooth.posli("H");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnNr.setToolTipText("zapnut rychlost \"najrychlejsie\"");
	    rdbtnNr.setBounds(10, 274, 107, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnNr);
	    
	    final JRadioButton rdbtnR = new JRadioButton("rychlo");
	    rdbtnR.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnR.isSelected()) {
	    			bluetooth.posli("I");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnR.setToolTipText("zapnut rychlost \"rychlo\"");
	    rdbtnR.setBounds(119, 274, 76, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnR);
	    
	    final JRadioButton rdbtnS = new JRadioButton("stredne");
	    rdbtnS.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnS.isSelected()) {
	    			bluetooth.posli("J");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnS.setToolTipText("zapnut rychlost \"stredne\"");
	    rdbtnS.setBounds(10, 314, 97, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnS);
	    
	    final JRadioButton rdbtnP = new JRadioButton("pomaly");
	    rdbtnP.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnP.isSelected()) {
	    			bluetooth.posli("K");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnP.setToolTipText("zapnut rychlost \"pomaly\"");
	    rdbtnP.setBounds(119, 314, 72, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnP);
	    
	   
	    
	    final JRadioButton rdbtnAcp = new JRadioButton("Acc doprava");
	    rdbtnAcp.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnAcp.isSelected()) {
	    			bluetooth.posli("M");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnAcp.setToolTipText("zapnut Acc doprava");
	    rdbtnAcp.setBounds(10, 371, 107, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnAcp);
	    
	    final JRadioButton rdbtnAcl = new JRadioButton("Acc dolava");
	    rdbtnAcl.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnAcl.isSelected()) {
	    			bluetooth.posli("L");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnAcl.setToolTipText("zapnut Acc dolava");
	    rdbtnAcl.setBounds(119, 371, 97, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnAcl);
	    
	    final JRadioButton rdbtnAcof = new JRadioButton("vypnut Acc");
	    rdbtnAcof.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnAcof.isSelected()) {
	    			bluetooth.posli("N");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnAcof.setToolTipText("vypnut Acc");
	    rdbtnAcof.setBounds(218, 371, 120, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnAcof);
	    
	    ButtonGroup group3 = new ButtonGroup();
	    group3.add(rdbtnAcl);
	    group3.add(rdbtnAcp);
	    group3.add(rdbtnAcof);
	    
	    final JCheckBox chckbxUltzSenzor = new JCheckBox("ultrazvukov\u00FD senzor");
	    chckbxUltzSenzor.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (chckbxUltzSenzor.isSelected()) {
	    			bluetooth.posli("F");
	    		} else {
	    			bluetooth.posli("G");
	    		}
	    	}
	    });
	    chckbxUltzSenzor.setBounds(10, 231, 165, 23);
	    frmOvladacRobota.getContentPane().add(chckbxUltzSenzor);
	    
	    scrollPane = new JScrollPane();
	    scrollPane.setBounds(10, 10, 973, 214);
	    
	    frmOvladacRobota.getContentPane().add(scrollPane);

	    listModel = new DefaultListModel();
	    list = new JList(listModel);
	    scrollPane.setViewportView(list);
	    
	    chckbxZastavRolovanie = new JCheckBox("zastav rolovanie");
	    chckbxZastavRolovanie.setBounds(863, 231, 120, 23);
	    frmOvladacRobota.getContentPane().add(chckbxZastavRolovanie);
	    
	    chckbxZastavPrimanie = new JCheckBox("zastav primanie");
	    chckbxZastavPrimanie.setBounds(726, 231, 114, 23);
	    frmOvladacRobota.getContentPane().add(chckbxZastavPrimanie);
	    
	    final JRadioButton rdbtnRS = new JRadioButton("stredne rychlo");
	    rdbtnRS.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnRS.isSelected()) {
	    			bluetooth.posli("O");
	    			} else {
	    		}
	    		
	    	}
	    });
	    
	   
	   
	    rdbtnRS.setToolTipText("zapnut rychlost \"stredne rychlo\"");
	    rdbtnRS.setBounds(208, 274, 120, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnRS);
	    
	    final JRadioButton rdbtnVS = new JRadioButton("viac stredne");
	    rdbtnVS.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnVS.isSelected()) {
	    			bluetooth.posli("P");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnVS.setToolTipText("zapnut rychlost \"viac stredne\"");
	    rdbtnVS.setBounds(208, 314, 120, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnVS);
	    
	    final JRadioButton rdbtnMS = new JRadioButton("menej stredne");
	    rdbtnMS.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnMS.isSelected()) {
	    			bluetooth.posli("Q");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnMS.setToolTipText("zapnut rychlost \"menej stredne\"");
	    rdbtnMS.setBounds(331, 274, 120, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnMS);
	    
	    JRadioButton rdbtnNp = new JRadioButton("najpomalsie");
	    rdbtnNp.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
	    		if (rdbtnRS.isSelected()) {
	    			bluetooth.posli("R");
	    			} else {
	    		}
	    	}
	    });
	    rdbtnNp.setToolTipText("zapnut rychlost \"najpomalsie\"");
	    rdbtnNp.setBounds(331, 314, 120, 37);
	    frmOvladacRobota.getContentPane().add(rdbtnNp);
	    
	    
	    
	    Zobrazovac zobrazovac = new Zobrazovac(bluetooth, this);
	    Thread thread = new Thread(zobrazovac);
	    thread.setDaemon(true);
	    thread.start();
	    
	    ButtonGroup group2 = new ButtonGroup();
	    group2.add(rdbtnNr);
	    group2.add(rdbtnR);
	    group2.add(rdbtnS);
	    group2.add(rdbtnP);
	    group2.add(rdbtnNp);
	    group2.add(rdbtnMS);
	    group2.add(rdbtnVS);
	    group2.add(rdbtnRS);
	}
	
	 
	    

	public void prisielRiadok(String riadok) {
		String x = null;
		int i = riadok.indexOf("Vzdialenost = ");
		if (i >= 0) {
			x = riadok.substring(13 + i);
		}
		textVzdialenost.setText(x);
		
		if (!chckbxZastavPrimanie.isSelected()) {
			listModel.addElement(riadok);
			if (!chckbxZastavRolovanie.isSelected()) {
				JScrollBar sb = scrollPane.getVerticalScrollBar();
				sb.setValue(sb.getMaximum());
			}
		}
	}
}
