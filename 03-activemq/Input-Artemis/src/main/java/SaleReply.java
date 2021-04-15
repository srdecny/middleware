import java.io.Serializable;

public class SaleReply implements Serializable {
    private static final long serialVersionUID = 0xDEADBEEF;

	public boolean accepted;
	public int accountNumber;
	public int price;

	public SaleReply(boolean accepted, int accountNumber, int price) {
		this.accepted = accepted;
		this.accountNumber = accountNumber;
		this.price = price;
	}
}