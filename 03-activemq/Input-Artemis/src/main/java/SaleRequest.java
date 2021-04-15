import java.io.Serializable;

public class SaleRequest implements Serializable {
    private static final long serialVersionUID = 0xC0FFEE;
	public String buyerName;
	public String goodsName;
	public int accountNumber;

	public SaleRequest(String buyerName, String goodsName, int accountNumber) {
		this.buyerName = buyerName;
		this.goodsName = goodsName;
		this.accountNumber = accountNumber;
	}
}